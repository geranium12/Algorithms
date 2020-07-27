#include <fstream>
#include <vector>
#include <string>

class DisjointSetUnion {
private:
	 long componentsNumber;
	std::vector< long> size;
	std::vector< long> parent;
public:
	DisjointSetUnion(const  long& n) {
		componentsNumber = n;
		size.resize(n);
		std::fill(size.begin(), size.end(), 1);
		parent.resize(n);
		for ( long i = 0; i < n; i++) {
			parent[i] = i;
		}
	}

	 long FindSet (long x) {
		if (parent[x] == x) {
			return x;
		}
		parent[x] = parent[FindSet(parent[x])];
		return parent[x];
	}

	void Union (long x,  long y) {
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

	bool isConnected() {
		return componentsNumber == 1;
	}
};

int main() {
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");

	long n, m, q;
	fin >> n >> m >> q;
	std::vector<std::pair< long,  long>> edges(m);
	std::vector< long> queries(q);

	std::vector<long> v(m);

	for (long i = 0; i < m; i++) {
		std::pair<long, long> p;
		fin >> p.first >> p.second;
		p.first--;
		p.second--;
		edges[i] = p;
		v[i] = 1;
	}

	for (long i = 0; i < q; i++) {
		fin >> queries[i];
		v[queries[i] - 1] = 0;
	}

	DisjointSetUnion dsu(n);

	for (int i = 0; i < v.size(); i++) {
		if (v[i] != 0) {
			dsu.Union(edges[i].first, edges[i].second);
		}
	}

	std::vector<int> ans(q);
	for (int i = ans.size() - 1; i >= 0; i--) {
		if (dsu.isConnected()) {
			ans[i] = 1;
		}
		else {
			ans[i] = 0;
		}
		dsu.Union(edges[queries[i] - 1].first, edges[queries[i] - 1].second);
	}

	for (int i = 0; i < ans.size(); i++) {
		fout << ans[i];
	}
	return 0;
}