#include "BooleanFunction.h"

using namespace std;

int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	string str;
	getline(fin, str);

	BooleanFunction f = str;
	vector<bool> res = f.getValueVector();
	for (size_t i = 0; i < res.size(); i++)
	{
		fout << res[i];
	}
	return 0;
}