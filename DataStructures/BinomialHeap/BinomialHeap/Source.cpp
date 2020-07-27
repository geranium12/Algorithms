#include <fstream>
#include <vector>

using namespace std;

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	long long n;
	fin >> n;
	vector<long> v;

	while (n != 0) {
		v.push_back(n % 2);
		n /= 2;
	}

	for (long i = 0; i < v.size(); i++) {
		if (v[i] == 1) {
			fout << i << endl;
		}
	}
	return 0;
}