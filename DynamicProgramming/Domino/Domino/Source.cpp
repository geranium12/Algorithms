#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	ifstream fin("in.txt");
	ofstream fout("out.txt");

	long n;
	fin >> n;
	vector<long> diff(n);
	vector<long> numberDiff(13, 0);
	long a, b, sum;
	sum = 0;
	for (long i = 0; i < n; i++) {
		fin >> a >> b;
		diff[i] = a - b;
		sum += diff[i];
		long d = diff[i] + 6;
		numberDiff[d]++;
	}

	vector<long> w;
	vector<long> p;

	for (long i = 0; i < numberDiff.size(); i++) {
		for (long j = 1; j <= numberDiff[i]; j = j * 2) {
			long domino = (i - 6) * j;
			w.push_back(domino);
			p.push_back(j);
			numberDiff[i] = numberDiff[i] - j;
		}
		if (numberDiff[i] > 0) {
			long j = numberDiff[i];
			long domino = (i - 6) * j;
			w.push_back(domino);
			p.push_back(j);
			//numberDiff[i] = 0;
		}
	}

	long size = n * 12;
	long div = n * 6;

	vector<vector<long>> A(w.size());
	for (long i = 0; i < A.size(); i++) {
		A[i] = vector<long>(size, LONG_MAX);
	}

	A[0][div + sum] = 0;
	for (long k = 1; k <= w.size(); k++) {
		for (long s = 0; s <= size; s++) {
			if (A[k - 1][s] != LONG_MAX) {
				A[k][s] = min(A[k - 1][s], A[k - 1][s - w[k - 1]] + p[k - 1]);
			}
			else {
				A[k][s] = A[k - 1][s];
			}
		}
	}

	return 0;
}