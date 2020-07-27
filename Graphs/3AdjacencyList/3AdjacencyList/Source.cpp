#include <fstream>
#include <vector>
#include <algorithm>

int main()
{
	std::string fileInputName = "input.txt";
	std::string fileOutputName = "output.txt";

	std::ifstream fin(fileInputName);
	int n, m;
	fin >> n >> m;

	std::vector<std::vector<int>> adjList(n);
	for (int i = 0; i < m; i++)
	{
		int x, y;
		fin >> x >> y;
		x--;
		y--;
		adjList[x].push_back(y);
		adjList[y].push_back(x);
	}

	std::ofstream fout(fileOutputName);
	for (int i = 0; i < adjList.size(); i++)
	{
		fout << adjList[i].size() << " ";
		for (int j = 0; j < adjList[i].size(); j++)
		{
			fout << adjList[i][j] + 1 << " ";
		}
		fout << std::endl;
	}
	return 0;
}