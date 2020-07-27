#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

void bfs(const vector<vector<int>>& adjList, vector<int>& colors, int k)
{
	int n = colors.size();
	queue<int> queue;
	queue.push(k);
	colors[k] = 1;

	while (!queue.empty())
	{
		int v = queue.front();
		queue.pop();
		for (int i = 0; i < adjList[v].size(); i++)
		{
			if (!colors[adjList[v][i]])
			{
				queue.push(adjList[v][i]);
				colors[adjList[v][i]] = colors[v] + 1;
			}
		}
	}
}

int main()
{
	// reading data
	ifstream fin("in.txt");
	ofstream fout("out.txt");
	int n;
	fin >> n;
	vector<vector<int>> adjList(n, vector<int>());
	int j;
	for (int i = 0; i < n; i++)
	{
		int x;
		fin >> j;
		while (j > 0)
		{
			fin >> x;
			if (x)
			{
				adjList[i].push_back(x - 1);
			}
			j--;
		}
	}

	// BFS
	vector<int> colors(n, 0);
	int maxValue = 0, maxPos = -1;
	for (int i = 0; i < n; i++)
	{
		colors.assign(n, 0);
		bfs(adjList, colors, i);
		bool f = true;
		for (int k = 0; k < colors.size(); k++) {
			if (!colors[k]) {
				f = false;
				break;
			}
		}
		if (f) 
		{
			for (int j = 0; j < n; j++)
			{
				if (maxValue <= colors[j] && maxPos <= i)
				{
					maxValue = colors[j];
					maxPos = i;
				}
			}
		}
	}

	// writing results
	if (!maxValue)
	{
		fout << "impossible";
		return 0;
	}

	fout << maxValue - 1 << endl;
	fout << maxPos + 1;
	return 0;
}