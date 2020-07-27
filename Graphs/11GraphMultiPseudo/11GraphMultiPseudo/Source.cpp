#include <fstream>
#include <vector>

using namespace std;

void outputResults(ofstream& fout, bool res)
{
	if (res)
	{
		fout << "Yes" << endl;
	}
	else
	{
		fout << "No" << endl;
	}
}

int main()
{
	//reading data
	string fileInputName = "input.txt";
	string fileOutputName = "output.txt";

	ifstream fin(fileInputName);
	int n, m;
	fin >> n >> m;

	vector<vector<int>> adjList(n);
	for (int i = 0; i < m; i++)
	{
		int x, y;
		fin >> x >> y;
		x--;
		y--;
		adjList[x].push_back(y);
		adjList[y].push_back(x);
	}

	//find if the graph includes loops or multiple edges
	bool loop = false;
	bool edge = false;
	for (int i = 0; i < adjList.size(); i++)
	{
		vector<int> arr(n, 0);
		for (int j = 0; j < adjList[i].size(); j++)
		{
			arr[adjList[i][j]]++;
		}

		if (arr[i])
		{
			loop = true;
		}

		int k = 0;
		while (k < arr.size() && arr[k] < 2)
		{
			k++;
		}
		if (k < n)
		{
			edge = true;
		}
		if (loop && edge)
		{
			break;
		}
	}
	
	ofstream fout(fileOutputName);
	bool simple, multi, pseudo;
	simple = multi = pseudo = false;
	if (loop == true)
	{
		pseudo = true;
	}
	else if (edge == true)
	{
		multi = pseudo = true;
	}
	else
	{
		simple = multi = pseudo = true;
	}
	outputResults(fout, simple);
	outputResults(fout, multi);
	outputResults(fout, pseudo);
	return 0;
}