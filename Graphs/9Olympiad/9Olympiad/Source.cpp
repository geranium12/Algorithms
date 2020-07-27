#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

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
	//reading data
	ifstream fin("input.in");
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
	dfs(0, adjList, colors);

	//writing results
	ofstream fout("output.out");
	int i = 0;
	while (i < n && colors[i] > 0)
	{
		i++;
	}
	if (i == n)
	{
		fout << "YES";
	}
	else
	{
		fout << "NO";
	}
	return 0;
}