#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void inputData(string fileName, vector<vector<int>>& adjList)
{
	ifstream fin(fileName);
	int n;
	fin >> n;

	adjList.resize(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int x;
			fin >> x;
			if (x)
			{
				adjList[i].push_back(j);
			}
		}
	}
}

void dfsModified(int i, const vector<vector<int>>& adjList, vector<int>& colors, int f, bool& res)
{
	colors[i] = f * -1;
	for (int j = 0; j < adjList[i].size(); j++)
	{
		if (colors[adjList[i][j]] == 0)
		{
			dfsModified(adjList[i][j], adjList, colors, colors[i], res);
		} 
		if (colors[i] == colors[adjList[i][j]])
		{
			res = true;
		}
	}
}

void outputResults(string fileOutputName, bool res, const vector<int>& colors)
{
	ofstream fout(fileOutputName);
	if (!res)
	{
		fout << "YES" << endl;
		int k = 0;
		for (int i = 0; i < colors.size() && k < colors.size() - 1; i++)
		{
			if (colors[i] < 0)
			{
				fout << i + 1 << " ";
				k++;
			}
		}
	}
	else
	{
		fout << "NO";
	}
}

int main()
{
	// reading data
	string fileInputName = "input.in";
	string fileOutputName = "output.out";

	vector<vector<int>> adjList;
	inputData(fileInputName, adjList);
	
	// DFS Modified
	int n = adjList.size();
	bool res = false;
	vector<int> colors(n, 0);
	for (int i = 0; i < n; i++)
	{
		if (colors[i] == 0)
		{
			dfsModified(i, adjList, colors, 1, res);
		}
		if (res == true)
		{
			break;
		}
	}

	outputResults(fileOutputName, res, colors);

	return 0;
}