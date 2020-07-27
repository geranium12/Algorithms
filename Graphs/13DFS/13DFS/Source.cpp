#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

void dfs(int i, const vector<vector<int>>& adjList, vector<int>& colors, int& k)
{
	k++;
	colors[i] = k;
	for (int j = 0; j < adjList[i].size(); j++)
	{
		if (colors[adjList[i][j]] == 0)
		{
			dfs(adjList[i][j], adjList, colors, k);
		}
	}

}

int main()
{
	//reading data
	ifstream fin("input.txt");
	int n;
	fin >> n;
	vector<vector<int>> adjList(n, vector<int>());
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int x;
			fin >> x;
			if (x == 1)
			{
				adjList[i].push_back(j);
			}
		}
	}

	// DFS
	vector<int> colors(n, 0);
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		if (colors[i] == 0)
		{
			dfs(i, adjList, colors, k);
		}
	}

	//writing results
	ofstream fout("output.txt");
	for (int i = 0; i < n; i++)
	{
		fout << colors[i] << " ";
	}
	return 0;
}