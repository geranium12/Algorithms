#include <fstream>
#include <algorithm>
#include <limits>

using namespace std;

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	long long n;
	fin >> n;
	long long* a = new long long[n + 1];
	long long prev;
	for (long long i = 0; i < n; i++) {
		fin >> a[i];
		fin >> prev;
	}
	a[n] = prev;

	long long** matrix = new long long*[n];
	for (long long i = 0; i < n; i++) {
		matrix[i] = new long long[n];
		for (long long j = 0; j < n; j++) {
			matrix[i][j] = numeric_limits<long long>::max();;
		}
		matrix[i][i] = 0;
	}

	for (long long i = 1; i < n; i++) {
		for (long long j = 0; j < n - i; j++) {
			for (long long k = j; k < j + i; k++) {
				matrix[j][j + i] = min(matrix[j][j + i], matrix[j][k] + matrix[k + 1][j + i] + a[j] * a[k + 1] * a[j + i + 1]);
			}
		}
	}

	fout << matrix[0][n - 1] << endl;
	return 0;
}