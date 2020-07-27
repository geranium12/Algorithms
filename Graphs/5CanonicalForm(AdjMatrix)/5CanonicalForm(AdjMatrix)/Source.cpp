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
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int x;
			fin >> x;
			if (x)
			{
				p[j] = i + 1;
			}
		}
	}

	std::ofstream fout(fileOutputName);
	for (int i = 0; i < n; i++)
	{
		fout << p[i] << " ";
	}
	return 0;
}