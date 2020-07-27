#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool binarySearch(vector<long long>& v, long long &x, long long& l, long long& r) {
	long long m;
	bool f;
	l = 0;
	r = v.size() - 1;
  	while (l <= r) {
		m = l + (r - l) / 2;
		
		if (v[l] == x && v[r] == x) {
			r++;
			return true;
		}

		if (v[m] == x) {
			f = true;
			if (m == l + 1 && v[l] != x) {
				l = m;
			}
			else {
				if (m == r - 1) {
					r = m;
					f = false;
				} 
				else {
					if (v[l] != x) {
						l++;
					}
					if (v[r] != x) {
						r--;
					}
				}
				
			}
		}
		else if (v[m] < x) {
			l = m + 1;	
		}
		else {
			r = m - 1;
		}
	}
	r = l;
	return false;
}

int main() {
	long long n;
	cin >> n;
	vector<long long> v(n);
	for (long long i = 0; i < n; i++) {
		cin >> v[i];
	}

	long long k, x, l, r;
	cin >> k;
	for (long long i = 0; i < k; i++) {
		cin >> x;
		bool b = binarySearch(v, x, l, r);
		cout << b << " " << l << " " << r << endl;
	}
	return 0;
}