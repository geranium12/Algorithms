#include <fstream>
#include <vector>
#include <algorithm>

int main()
{
	std::string fileInputName = "input.txt";
	std::string fileOutputName = "output.txt";

	std::ifstream fin(fileInputName);
	int n;
	fin >> n;

	std::vector<int> p(n);
	for (int i = 0; i < n - 1; i++)
	{
		int x, y;
		fin >> x >> y;
		y--;
		p[y] = x;
	}

	std::ofstream fout(fileOutputName);
	for (int i = 0; i < n; i++)
	{
		fout << p[i] << " ";
	}
	return 0;
}