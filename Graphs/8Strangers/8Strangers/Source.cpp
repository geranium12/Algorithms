#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

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

bool bfsModified(const vector<vector<int>>& adjList, vector<int>& colors)
{
	int n = adjList.size();
	colors.resize(n, 0);
	int f = 1;
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
		colors[i] = f;
		f *= -1;
		queue.push(i);

		while (!queue.empty())
		{
			int v = queue.front();
			queue.pop();
			for (int i = 0; i < adjList[v].size(); i++)
			{
				int t = adjList[v][i];
				if (!colors[t])
				{
					k++;
					queue.push(t);
					colors[t] = colors[v] * -1;
				}
				else if (colors[t] == colors[v])
				{
					return false;
				}
			}
		}
	}
	return true;
}

void outputResults(string fileOutputName, bool res, const vector<int>& colors)
{
	ofstream fout(fileOutputName);
	if (res)
	{
		fout << "YES" << endl;
		int k = 0;
		for (int i = 0; i < colors.size() && k < colors.size() - 1; i++)
		{
			if (colors[i] > 0)
			{
				fout << i << " ";
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
	
	vector<int> colors;
	outputResults(fileOutputName, bfsModified(adjList, colors), colors);

	return 0;
}