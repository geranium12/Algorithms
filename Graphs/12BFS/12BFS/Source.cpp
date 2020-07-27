#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
	// reading data
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

	// BFS
	vector<int> colors(n, 0);
	int k = 0;
	queue<int> queue;
	while (k < n)
	{
		int i = 0;
		while (i < n && colors[i] > 0)
		{
			i++;
		}
		k++;
		colors[i] = k;
		queue.push(i);

		while (!queue.empty())
		{
			int v = queue.front();
			queue.pop();
			for (int i = 0; i < adjList[v].size(); i++)
			{
				if (colors[adjList[v][i]] == 0)
				{
					k++;
					queue.push(adjList[v][i]);
					colors[adjList[v][i]] = k;
				}
			}
		}		
	}

	// writing results
	ofstream fout("output.txt");
	for (int i = 0; i < n; i++)
	{
		fout << colors[i] << " ";
	}
	return 0;
}