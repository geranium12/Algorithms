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
	std::vector<std::vector<int>> mat(n, std::vector<int>(n));
	for (int i = 0; i < m; i++)
	{
		int x, y;
		fin >> x >> y;
		x--;
		y--;
		mat[x][y] = 1;
		mat[y][x] = 1;
	}

	std::ofstream fout(fileOutputName);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			fout << mat[i][j] << " ";
		}
		fout << std::endl;
	}
	return 0;
}