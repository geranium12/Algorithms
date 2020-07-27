#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
#include <limits>

std::ifstream fin("input.in");
std::ofstream fout("output.out");

void printMatrix(std::vector<std::vector<long>>& mat) {
	for (int i = 0; i < mat.size(); i++) {
		for (int j = 0; j < mat[i].size(); j++) {
			fout << mat[i][j] << " ";
		}
		fout << std::endl;
	}
	fout << std::endl;
}

long FindFlow(std::vector<std::vector<long>>& mat, std::vector<bool>& used, std::vector<bool> visited, long entry, long value) {
	long exit = mat.size() - 1;
	if (entry == exit) {
		return value;
	}
	used[entry] = true;
	for (long i = 0; i < used.size(); i++) {
		long c = mat[entry][i];
		if (!used[i] && c > 0) {
			long ret = FindFlow(mat, used, visited, i, std::min(value, c));
			fout << entry << " " << i << std::endl;
			if (ret > 0) {
				mat[entry][i] -= ret;
				mat[i][entry] += ret;
				printMatrix(mat);
				return ret;
			}
		}
	}
	return 0;
}

long FordFalkerson(std::vector<std::vector<long>>& mat) {
	long n = mat.size();
	std::vector<bool> used(n, false);
	std::vector<bool> visited(n, false);
	long ret, answer = 0;
	long value = std::numeric_limits<long>::max();
	do {
		fout << "FIND FLOW" << std::endl;
		ret = FindFlow(mat, used, visited, 0, value);
		answer += ret;
		std::fill(used.begin(), used.end(), false);
	} while (ret != 0);
	return answer;
}

int main() {
	long n, p, k;
	fin >> n >> p >> k;
	std::vector<std::vector<long>> mat(n + 2);
	mat[0] = std::vector<long>(n + 2);
	mat[n + 1] = std::vector<long>(n + 2);

	for (long i = 1; i < n + 1; i++) {
		mat[i] = std::vector<long>(n + 2);
		for (long j = 1; j < n + 1; j++) {
			fin >> mat[i][j];
		}
	}

	long entry, exit;
	for (long i = 0; i < p; i++) {
		fin >> entry;
		mat[0][entry]++;
		mat[entry][0]++;
	}

	for (long i = 0; i < k; i++) {
		fin >> exit;
		mat[n + 1][exit]++;
		mat[exit][n + 1]++;
	}

	fout << FordFalkerson(mat);
	return 0;
}