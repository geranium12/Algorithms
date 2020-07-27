#include <fstream>
#include <vector>
#include <string>

class DisjointSetUnion {
private:
	long long componentsNumber;
	std::vector<long long> size;
	std::vector<long long> parent;
public:
	DisjointSetUnion(const long long& n) {
		componentsNumber = n;
		size.resize(n);
		std::fill(size.begin(), size.end(), 1);
		parent.resize(n);
		for (long long i = 0; i < n; i++) {
			parent[i] = i;
		}
	}

	long long FindSet(long long x) {
		if (parent[x] == x) {
			return x;
		}
		parent[x] = parent[FindSet(parent[x])];
		return parent[x];
	}

	void Union(long long x, long long y) {
		x = FindSet(x);
		y = FindSet(y);
		if (x != y) {
			if (size[x] > size[y]) {
				std::swap(x, y);
			}
			parent[x] = y;
			size[y] += size[x];
			componentsNumber--;
		}
	}

	long long getComponentsNumber() {
		return componentsNumber;
	}
};

int main() {
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");

	long long n, q;
	fin >> n >> q;
	DisjointSetUnion dsu(n);

	std::string s;
	for (long long i = 0; i < q; i++) {
		long long x, y;
		fin >> x >> y;
		x--;
		y--;
		dsu.Union(x, y);
		s += std::to_string(dsu.getComponentsNumber());
		s += "\n";
	}

	fout << s;
	return 0;
}