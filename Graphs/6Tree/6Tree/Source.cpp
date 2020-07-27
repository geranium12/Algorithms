#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
	ifstream fin("input.txt");
	int n, m = 0;
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
				m++;
				adjList[i].push_back(j);
			}
		}
	}

	vector<int> colors(n, 0);
	colors[0] = 1;
	queue<int> queue;
	queue.push(0);
	while (!queue.empty())
	{
		int v = queue.front();
		queue.pop();
		for (int i = 0; i < adjList[v].size(); i++)
		{
			if (colors[adjList[v][i]] == 0)
			{
				queue.push(adjList[v][i]);
				colors[adjList[v][i]]++;
			}
		}
		colors[v]++;
	}

	ofstream fout("output.txt");
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		if (colors[i] < 2)
		{
			k++;
		}
	}
	if (k > 0 || (m / 2) != n - 1)
	{
		fout << "No";
	}
	else
	{
		fout << "Yes";
	}
	return 0;
}