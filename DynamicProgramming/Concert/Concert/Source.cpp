#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

#define MAX_LONG numeric_limits<long long>::max();

bool doesItFit(long long a, long long b, long long m, long long d) {
	if ((a < d && b < m) || (a == 0 && b == m)) {
		return true;
	}
	return false;
}

int main() {
	ifstream fin("concert.in");
	ofstream fout("concert.out");

	int n;
	long long m, d;
	fin >> n >> m >> d;

	vector<long long> a;
	long long x;
	for (int i = 0; i < n; i++) {
		fin >> x;
		if (x <= d) {
			a.push_back(x);
		}
	}

	n = a.size();
	vector<pair<long long, long long>> f(n);
	int maxN = 0;

	for (int i = 0; i < n; i++) {
		f[i].first = f[i].second = MAX_LONG;
	}
	
	pair<long long, long long> p;

	for (int i = 0; i < n; i++) {
		for (int j = i; j >= 0; j--) {
			if (j == 0) {
				p.first = a[i] % d;
				p.second = a[i] / d;
			}
			else if (a[i] > (d - f[j - 1].first)) {
					p.first = a[i] % d;
					p.second = f[j - 1].second + 1 + (a[i] / d);
				}
			else if (a[i] == (d - f[j - 1].first)) {
				p.first = 0;
				p.second = f[j - 1].second + 1;
			}
			else {
					p.first = f[j - 1].first + a[i];
					p.second = f[j - 1].second;
				}
			if (doesItFit(p.first, p.second, m, d) && (j + 1) > maxN) {
				maxN = j + 1;
			}
			if ((f[j].second > p.second) || (f[j].second == p.second && f[j].first > p.first)) {
				f[j] = p;
			}
		}
	}
	fout << maxN << endl;
	return 0;
}