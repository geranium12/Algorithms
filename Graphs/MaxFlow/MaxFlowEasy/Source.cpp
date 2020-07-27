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

long FordFalkerson(std::vector<std::vector<std::pair<long, long>>>& adjList, std::vector<long>& marked, long exit) {
	std::vector<bool> used(adjList.size(), false);
	long ret, answer = 0;
	constexpr long value = std::numeric_limits<long>::max();

	do {
		ret = FindFlow(adjList, used, marked, 0, exit, value);
		answer += ret;
		std::fill(used.begin(), used.end(), false);
	} while (ret != 0);

	return answer;
}

int main() {
	long n, m, a, b, c;
	std::cin >> n >> m;

	std::vector<std::vector<std::pair<long, long>>> adjList(n);
	std::vector<long> marked(n, 0);
	std::pair<long, long> pair;

	for (long i = 0; i < m; i++) {
		long x, y, z;
		std::cin >> x >> y >> z;
		x--;
		y--;
		pair = std::make_pair(y, z);
		adjList[x].push_back(pair);
		pair = std::make_pair(x, 0);
		adjList[y].push_back(pair);
	}

	long answer = FordFalkerson(adjList, marked, n - 1);
	std::cout << answer;
	return 0;
}