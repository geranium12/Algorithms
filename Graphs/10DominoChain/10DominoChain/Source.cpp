#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void dfs(int i, const vector<vector<int>>& adjList, vector<int>& colors)
{
	colors[i]++;
	for (int j = 0; j < adjList[i].size(); j++)
	{
		if (colors[adjList[i][j]] == 0)
		{
			dfs(adjList[i][j], adjList, colors);
		}
	}
}

int main()
{
	const int NUMBER_OF_POINTS = 7;

	string fileInputName = "input.txt";
	string fileOutputName = "output.txt";

	ifstream fin(fileInputName);
	ofstream fout(fileOutputName);
	int n;
	fin >> n;

	vector<vector<int>> adjList(NUMBER_OF_POINTS);
	int t;
	for (int i = 0; i < n; i++)
	{
		int x, y;
		fin >> x >> y;
		adjList[x].push_back(y);
		adjList[y].push_back(x);
		t = x;
	}

	// check if degV is odd => No
	for (int i = 0; i < NUMBER_OF_POINTS; i++)
	{
		if (adjList[i].size() % 2)
		{
			fout << "No";
			return 0;
		}
	}

	// check if the graph is connected (can include isolated vertices) 
	vector<int> colors(NUMBER_OF_POINTS, 0);
	dfs(t, adjList, colors);

	for (int i = 0; i < NUMBER_OF_POINTS; i++)
	{
		if (!colors[i] && adjList[i].size())
		{
			fout << "No";
			return 0;
		}
	}

	fout << "Yes";

	return 0;
}