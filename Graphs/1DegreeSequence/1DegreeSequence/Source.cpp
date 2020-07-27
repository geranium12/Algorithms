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
	std::vector<int> v(n);
	for (int i = 0; i < 2 * m; i++)
	{
		int x;
		fin >> x;
		v[x - 1]++;
	}
	
	std::sort(v.begin(), v.end(), std::greater<int>());

	std::ofstream fout(fileOutputName);
	for (int i = 0; i < v.size(); i++) 
	{
		fout << v[i] << " ";
	}
	return 0;
}