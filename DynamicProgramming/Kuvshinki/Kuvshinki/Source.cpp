#include <fstream>
#include <algorithm>

using namespace std;

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	int n;
	fin >> n;
	int *a = new int[n];
	for (int i = 0; i < n; i++) {
		fin >> a[i];
	}

	if (n < 3) {
		if (n == 1) {
			fout << a[0] << endl;
		}
		else {
			fout << -1 << endl;
		}
	}
	else {
		int* f = new int[n];
		fill(f, f + n, -1);

		f[0] = f[2] = a[0];
		f[2] += a[2];
		for (int i = 3; i < n; i++) {
			f[i] = max(f[i - 2], f[i - 3]) + a[i];
		}

		fout << f[n - 1] << endl;
	}
	return 0;
}