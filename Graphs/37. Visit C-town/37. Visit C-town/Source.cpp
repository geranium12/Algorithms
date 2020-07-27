#include <fstream>
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <limits>

long FindFlow(std::vector<std::vector<std::pair<long, long>>>& adjList, std::vector<bool>& used, std::vector<long>& marked,
	long entry, long exit, long value) {
	if (entry == exit) {
		return value;
	}
	used[entry] = true;
	for (long i = 0; i < adjList[entry].size(); i++) {
		long f = adjList[entry][i].first;
		long c = adjList[entry][i].second;
		if (!used[f] && c > 0) {
			long ret = FindFlow(adjList, used, marked, f, exit, std::min(value, c));
			if (ret > 0) {
 				adjList[entry][i].second -= ret;
				for (int j = 0; j < adjList[f].size(); j++) {
					if (adjList[f][j].first == entry) {
						adjList[f][j].second += ret;
						return ret;
					}
				}
				return ret;
				}
			}
		}
	return 0;
}

bool FordFalkerson(std::vector<std::vector<std::pair<long, long>>>& adjList, std::vector<long>& marked, long exit) {
	std::vector<bool> used(adjList.size(), false);
	long ret, answer = 0;
	constexpr long value = std::numeric_limits<long>::max();

	do {
		ret = FindFlow(adjList, used, marked, 0, exit, value);
		answer += ret;
		if (answer >= 2) {
			return true;
		}
		std::fill(used.begin(), used.end(), false);
	} while (ret != 0);

	if (answer >= 2) {
		return true;
	}
	return false;
}

int main() {
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");

	long n, m, a, b, c;
	fin >> n >> m;

	std::vector<std::vector<std::pair<long, long>>> adjList(n + 2);
	std::vector<long> marked(n + 2, 0);
	std::pair<long, long> pair;

	for (long i = 0; i < m; i++) {
		long x, y;
		fin >> x >> y;	
		pair = std::make_pair(y, 1);
		adjList[x].push_back(pair);
		pair = std::make_pair(x, 1);
		adjList[y].push_back(pair);
	}

	fin >> a >> b >> c;
	
	pair = std::make_pair(a, 1);
	adjList[0].push_back(pair);
	pair = std::make_pair(0, 1);
	adjList[a].push_back(pair);

	pair = std::make_pair(b, 1);
	adjList[0].push_back(pair);
	pair = std::make_pair(0, 1);
	adjList[b].push_back(pair);

	for (int i = 1; i < n + 1; i++) {
		if (i != c) {
			adjList.push_back(adjList[i]);
			marked[i] = adjList.size() - 1;
			marked.push_back(i);

			pair = std::make_pair(i, 1);
			adjList[adjList.size() - 1].push_back(pair);

			for (int j = 0; j < adjList[i].size(); j++) {
				long v = adjList[adjList.size() - 1][j].first;
				pair = std::make_pair(adjList.size() - 1, 0);
				adjList[v].push_back(pair);
			}

			std::vector<std::pair<long, long>> row = adjList[i];
			adjList[i].clear();
			pair = std::make_pair(adjList.size() - 1, 1);
			adjList[i].push_back(pair);
			for (int j = 0; j < row.size(); j++) {
				if (row[j].second == 0) {
					adjList[i].push_back(row[j]);
				}
			}
		}
	}

	for (int i = 0; i < adjList.size(); i++) {
		fout << "i = " << i << std::endl;
		for (int j = 0; j < adjList[i].size(); j++) {
			fout << adjList[i][j].first << " ";
		}
		fout << std::endl;
	}
	
	bool answer = FordFalkerson(adjList, marked, c);
	if (answer) {
		fout << "Yes";
	}
	else {
		fout << "No";
	}
	return 0;
}