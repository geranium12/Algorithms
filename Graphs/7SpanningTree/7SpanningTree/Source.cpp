#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void dfs(int i, const vector<vector<int>>& adjList, vector<int>& colors, vector<pair<int, int>>& edges)
{
	colors[i]++;
	for (int j = 0; j < adjList[i].size(); j++)
	{
		if (colors[adjList[i][j]] == 0)
		{
			edges.push_back(make_pair(i, adjList[i][j]));
			dfs(adjList[i][j], adjList, colors, edges);
		}
	}

}

int main()
{
	string fileInputName = "input.txt";
	string fileOutputName = "output.txt";

	ifstream fin(fileInputName);
	int n;
	fin >> n;

	vector<vector<int>> adjList(n);
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

	vector<int> colors(n, 0);
	vector<pair<int, int>> edges;
	dfs(0, adjList, colors, edges);

	ofstream fout(fileOutputName);
	int i = 0;
	while (i < n && colors[i] != 0)
	{
		i++;
	}
	if (i == n)
	{
		fout << edges.size() << endl;
		for (int i = 0; i < edges.size(); i++)
		{
			fout << edges[i].first + 1 << " " << edges[i].second + 1 << endl;
		}
	}
	else
	{
		fout << -1;
	}
	return 0;
}