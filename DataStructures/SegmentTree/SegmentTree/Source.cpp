#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

class SegmentTree {
	private:
		long long n;
		std::vector<long long> t;

		void DoBuild(std::vector<long long>& v, long long index, long long tl, long long tr) {
			if (tl >= tr) {
				return;
			}
			if (tr - tl == 1) {
				t[index] = v[tl];
				return;
			}
			long long m = (tl + tr) / 2;
			DoBuild(v, index * 2, tl, m);
			DoBuild(v, index * 2 + 1, m, tr);
			t[index] = t[index * 2] + t[index * 2 + 1];
		}

		void DoAdd(long long index, long long tl, long long tr, long long i, long long x) {
			if (tr - tl == 1) {
				t[index] += x;
			}
			else {
				long long m = (tr + tl) / 2;
				if (i < m) {
					DoAdd(2 * index, tl, m, i, x);
				}
				else {
					DoAdd(2 * index + 1, m, tr, i, x);
				}
				t[index] = t[2 * index] + t[2 * index + 1];
			}
		}

		long long DoFindSum(long long index, long long tl, long long tr, long long l, long long r) {
			if (l >= r) {
				return 0;
			}
			if (tl == l && tr == r) {
				return t[index];
			}
			else {
				long long m = (tl + tr) / 2;
				return (DoFindSum(2 * index, tl, m, l, std::min(m, r)) + DoFindSum(2 * index + 1, m, tr, std::max(m, l), r));
			}
		}

	public:
		SegmentTree(std::vector<long long>& v) {
			this->n = v.size();
			this->t = std::vector<long long>(n * 4 + 1, 0);
			DoBuild(v, 1, 0, n);
		}

		void Add(long long i, long long x) {
			DoAdd(1, 0, n, i, x);
		}

		long long FindSum(long long l, long long r) {
			return DoFindSum(1, 0, n, l, r);
		}

		void print() {
			for (int i = 0; i < t.size(); i++) {
				std::cout << t[i] << " ";
			}
			std::cout << std::endl;
		}
};

int main() {
	long long n;
	std::cin >> n;
	std::vector<long long> v(n);
	for (long long i = 0; i < n; i++) {
		std::cin >> v[i];
	}
	SegmentTree tree(v);

	long long k;
	std::cin >> k;
	long long a, b;
	std::string str;
	for (long long i = 0; i < k; i++) {
		std::cin >> str;
		std::cin >> a;
		std::cin >> b;
		if (str == "Add") {
			tree.Add(a, b);
		}
		else {
			std::cout << tree.FindSum(a, b) << std::endl;
		}
	}
	return 0;
}