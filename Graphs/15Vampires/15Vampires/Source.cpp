#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

void bfs(vector<vector<int>>& adjMat, queue<pair<int, int>>& queue, int& max)
{
	int i, j;
	while (!queue.empty())
	{
		pair<int, int> v = queue.front();
		queue.pop();
		i = v.first;
		j = v.second;
		if ((!adjMat[i + 1][j]) || (adjMat[i + 1][j] > adjMat[i][j] + 1))
		{
			adjMat[i + 1][j] = adjMat[i][j] + 1;
			queue.push(make_pair(i + 1, j));
		}
		if ((!adjMat[i - 1][j]) || (adjMat[i - 1][j] > adjMat[i][j] + 1))
		{
			adjMat[i - 1][j] = adjMat[i][j] + 1;
			queue.push(make_pair(i - 1, j));
		}
		if ((!adjMat[i][j + 1]) || (adjMat[i][j + 1] > adjMat[i][j] + 1))
		{
			adjMat[i][j + 1] = adjMat[i][j] + 1;
			queue.push(make_pair(i, j + 1));
		}
		if ((!adjMat[i][j - 1]) || (adjMat[i][j - 1] > adjMat[i][j] + 1))
		{
			adjMat[i][j - 1] = adjMat[i][j] + 1;
			queue.push(make_pair(i, j - 1));
		}
		max = adjMat[i][j] + 1;
	}
}

int main()
{
	// reading data
	ifstream fin("vampires.in");
	ofstream fout("vampires.out");
	int n, m;
	fin >> n >> m;
	vector<vector<int>> adjMat(n + 2, vector<int> (m + 2));
	
	for (int i = 0; i < m + 2; i++)
	{
		adjMat[0][i] = -1;
		adjMat[n + 1][i] = -1;
	}
	for (int i = 0; i < n + 2; i++)
	{
		adjMat[i][0] = -1;
		adjMat[i][m + 1] = -1;
	}

	char x;
	vector<pair<int, int>> vampires;
	for (int i = 1; i < n + 1; i++)
	{
		for (int j = 1; j < m + 1; j++)
		{
			fin >> x;
			switch (x)
			{
			case 'V':
				adjMat[i][j] = 1;
				vampires.push_back(make_pair(i, j));
				break;
			case '#':
				adjMat[i][j] = -1;
				break;
			default:
				adjMat[i][j] = 0;
			}
		}
	}

	// BFS
	int max = 0;
	queue<pair<int, int>> queue;
	for (int i = 0; i < vampires.size(); i++)
	{
		queue.push(vampires[i]);
	}
	bfs(adjMat, queue, max);

	// writing results
	fout << max - 2 << endl;
	return 0;
}