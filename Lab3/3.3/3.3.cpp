#include <fstream>
#include <iostream>
#include <limits>
#include <optional>
#include <string>
#include <iomanip>
#include <vector>
#include <set>

using namespace std;

vector<int> used, d, up;
set<int> artPoints;

bool CopyIntFromFileToArray(istream& inFile, vector<vector<int>>& graph)
{
	string str;
	inFile >> str;
	const int matrixSize = stoi(str);
	graph.resize(matrixSize);
	for (int i = 0; i < matrixSize; i++)
	{
		graph[i].resize(matrixSize);
		for (int j = 0; j < matrixSize; j++)
		{
			if (inFile.eof())
			{
				return false;
			}
			else
			{
				inFile >> str;
				size_t notDigitPosition = str.find_first_not_of("0123456789", 0);
				if (notDigitPosition == numeric_limits<size_t>::max())
				{
					graph[i][j] = stoi(str);
				}
			}
		}
	}

	return true;
}

vector<vector <double>> fillKirchhoffMatrix(vector<vector<int>>& graph)
{
	vector<vector<double>> kirchhoffMatrix;
	kirchhoffMatrix.resize(graph.size());
	for (int i = 0; i < graph.size(); i++)
	{
		kirchhoffMatrix[i].resize(graph.size());
		for (int j = 0; j < graph.size(); j++)
		{
			if (graph[i][j] != 0)
			{
				kirchhoffMatrix[i][j] = -1;
				kirchhoffMatrix[i][i] = kirchhoffMatrix[i][i] + 1;
			}
		}
	}

	return kirchhoffMatrix;
}

vector<vector <double>> fillMinor(vector<vector<double>>& matrix)
{
	vector<vector<double>> minor;

	minor.resize(matrix.size() - 1);

	for (int i = 0; i < matrix.size() - 1; i++) {
		minor[i].resize(matrix.size() - 1);
	}

	for (int i = 0; i < matrix.size() - 1; i++) {
		for (int j = 0; j < matrix.size() - 1; j++) {
			minor[i][j] = matrix[i][j];
		}
	}

	return minor;
}

bool CopyGraphFromFileToArray(const string& inputFileName, vector<vector<int>>& graph)
{
	ifstream inputFile;

	inputFile.open(inputFileName);
	if (!inputFile.is_open())
	{
		cout << "Failed to open " << inputFileName << " for reading\n";
		return false;
	}

	if (!CopyIntFromFileToArray(inputFile, graph))
	{
		cout << "Failed to copy data from " << inputFileName << " to matrix. Wrong input data\n";
		return false;
	}

	if (inputFile.bad())
	{
		cout << "Failed to read data from input file\n";
		return false;
	}

	return true;
}

void PrintMatrix(vector<vector<double>> matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.size(); j++)
		{
			cout << setw(6) << setprecision(4) << matrix[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;
}

bool getMinimalCosts(const string& inputFileName)
{
	vector<vector<int>> graph;

	if (!CopyGraphFromFileToArray(inputFileName, graph))
	{
		return false;
	}

	vector<vector<double>> kirchhoffMatrix = fillKirchhoffMatrix(graph);

	PrintMatrix(kirchhoffMatrix);

	vector<vector<double>> minor = fillMinor(kirchhoffMatrix);

	PrintMatrix(minor);

	const double EPS = 0.000000001;
	double det = 1;
	for (int i = 0; i < minor.size(); ++i) {
		int k = i;
		for (int j = i + 1; j < minor.size(); ++j)
			if (abs(minor[j][i]) > abs(minor[k][i]))
			{
				k = j;
			}
		if (abs(minor[k][i]) < EPS) {
			det = 0;
			break;
		}

		swap(minor[i], minor[k]);

		if (i != k)
		{
			det = -det;
		}
		det *= minor[i][i];
		for (int j = i + 1; j < minor.size(); ++j)
		{
			minor[i][j] /= minor[i][i];
		}
		for (int j = 0; j < minor.size(); ++j)
		{
			if (j != i && abs(minor[j][i]) > EPS)
			{
				for (int k = i + 1; k < minor.size(); ++k)
				{
					minor[j][k] -= minor[i][k] * minor[j][i];
				}
			}
		}
	}

	cout << det;


}


int main() {

	if (!getMinimalCosts("graph.txt"))
	{
		return 1;
	}

	return 0;

}