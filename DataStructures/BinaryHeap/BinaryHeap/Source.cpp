#include <fstream>
#include <vector>

using namespace std;

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	long n;
	fin >> n;
	vector<long> v(n);
	for (int i = 0; i < n; i++) {
		fin >> v[i];
	}

	bool f = true;
	for (int i = 1; i <= n && f; i++) {
		long a = 2 * i;
		long b = 2 * i + 1;
		if (a <= n && v[i - 1] > v[a - 1]) {
			f = false;
		}
		if (b <= n && v[i - 1] > v[b - 1]) {
			f = false;
		}
	}

	if (f) {
		fout << "Yes" << endl;
	}
	else {
		fout << "No" << endl;
	}
	return 0;
}