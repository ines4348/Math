#include<iostream>
#include<algorithm>
#include<fstream>
#include<string>
#include<set>
#include<vector>

using namespace std;

vector<vector<int>> graph;
vector<int> used, d, up;
set<int> artPoints;

vector<int> parse(string expression) {
    vector<int> v;
    string tempChar;
    string tempSubStr;
    int edgeStart, edgeEnd;

    for (int i = 0; i < expression.length(); i++)
    {
        tempChar = expression[i];

        if (tempChar == " ")
        {
            edgeStart = stoi(tempSubStr);
            tempSubStr = "";
        }
        else
        {
            tempSubStr += tempChar;
        }
    }

    edgeEnd = stoi(tempSubStr);

    v.push_back(edgeStart);
    v.push_back(edgeEnd);
    return v;
}

void dfs(int time, int v, int p = -1) {
    int i, to, children;
    used[v] = 1;

    d[v] = up[v] = time++;

    children = 0;

    for (i = 0; i < graph[v].size(); i++) {
        to = graph[v][i];

        if (to == p)  continue;
        if (used[to])
        {
            up[v] = min(up[v], d[to]);
        }
        else
        {
            dfs(time, to, v);

            up[v] = min(up[v], up[to]);
            if ((up[to] >= d[v]) && (p != -1)) {
                artPoints.insert(v);
            }
            children++;
        }
    }
    if ((p == -1) && (children > 1))
    {
        artPoints.insert(v);
    }
}

int main() {
    int n, m;
    int time;
    string expression;

    auto print = [](const int& el) { cout << el << " "; };

    std::ifstream inFile("graph.txt");

    if (inFile.is_open())
    {
        getline(inFile, expression);
        vector<int> temp = parse(expression);
        n = temp[0];
        m = temp[1];
        graph.resize(n + 1);
        used.resize(n + 1);
        d.resize(n + 1);
        up.resize(n + 1);

        while (getline(inFile, expression))
        {
            if (expression.length() > 0) {
                vector<int> temp2 = parse(expression);

                graph[temp2[0]].push_back(temp2[1]); graph[temp2[1]].push_back(temp2[0]);
            }
        }

        time = 1;
        for (int i = 1; i <= n; i++) {
            if (!used[i]) {
                dfs(time, i);
            }
        }

        for_each(artPoints.begin(), artPoints.end(), print);
        std::cout << "\n";
    }
    else {
        cout << "File error!" << endl;
        return 1;
    }
}