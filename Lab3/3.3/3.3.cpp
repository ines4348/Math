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

bool CopyDoubleFromFileToArray(std::istream& inFile, vector<vector<int>>& graph)
{
	std::string str;
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

bool CopyMatrixFromFileToArray(const std::string& inputFileName, vector<vector<int>>& graph)
{
	std::ifstream inputFile;

	inputFile.open(inputFileName);
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open " << inputFileName << " for reading\n";
		return false;
	}

	if (!CopyDoubleFromFileToArray(inputFile, graph))
	{
		std::cout << "Failed to copy data from " << inputFileName << " to matrix. Wrong input data\n";
		return false;
	}

	if (inputFile.bad())
	{
		std::cout << "Failed to read data from input file\n";
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
			std::cout << std::setw(6) << std::setprecision(4) << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
}

bool CountSpanningTrees(const std::string& inputFileName)
{
	vector<vector<int>> graph;

	if (!CopyMatrixFromFileToArray(inputFileName, graph))
	{
		return false;
	}

	vector<vector<double>> kirchhoffMatrix = fillKirchhoffMatrix(graph);

	PrintMatrix(kirchhoffMatrix);

	vector<vector<double>> minor = fillMinor(kirchhoffMatrix);

	PrintMatrix(minor);

	const double EPS = 1E-9;
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

	if (!CountSpanningTrees("graph.txt"))
	{
		return 1;
	}

	return 0;

}