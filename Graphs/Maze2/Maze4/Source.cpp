#include <fstream> 
#include <iostream>
#include <limits.h> 
#include <string.h> 
#include <queue> 
#include <vector>

std::ifstream fin("input.in");
std::ofstream fout("output.out");

bool BFS(std::vector<std::vector<long>>& graph, long s, long t, std::vector<long>& parent)
{
	long n = graph.size();
	std::vector<bool> visited(n, false);

	std::queue<long> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	while (!q.empty())
	{
		long u = q.front();
		q.pop();

		for (long v = 0; v < n; v++)
		{
			if (visited[v] == false && graph[u][v] > 0)
			{
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}

	return (visited[t] == true);
}

long FordFulkerson(std::vector<std::vector<long>>& graph, long s, long t)
{
	long n = graph.size();
	long u, v;
	long max_flow = 0;

	std::vector<long> parent(n);
	while (BFS(graph, s, t, parent))
	{
		long path_flow = LONG_MAX;
		for (v = t; v != s; v = parent[v])
		{
			u = parent[v];
			path_flow = std::min(path_flow, graph[u][v]);
		}

		for (v = t; v != s; v = parent[v])
		{
			u = parent[v];
			std::cout << u << " " << v << std::endl;
			graph[u][v] -= path_flow;
			graph[v][u] += path_flow;
		}

		max_flow += path_flow;
	}

	for (int i = 0; i < graph.size(); i++) {
		for (int j = 0; j < graph[i].size(); j++) {
			if (graph[i][j] > 0) {
				fout << i << " " << j << " " << graph[i][j] << std::endl;
			}
		}
		fout << std::endl;
	}

	return max_flow;
}

int main()
{
	long n, p, k;
	fin >> n >> p >> k;

	std::vector<std::vector<long>> graph(n + 2);
	graph[0] = std::vector<long>(n + 2);
	graph[n + 1] = std::vector<long>(n + 2);

	for (long i = 1; i < n + 1; i++) {
		graph[i] = std::vector<long>(n + 2);
		for (long j = 1; j < n + 1; j++) {
			fin >> graph[i][j];
		}
	}

	long entry, exit;
	for (long i = 0; i < p; i++) {
		fin >> entry;
		graph[0][entry]++;
		graph[entry][0]++;
	}

	for (long i = 0; i < k; i++) {
		fin >> exit;
		graph[n + 1][exit]++;
		graph[exit][n + 1]++;
	}

	std::vector<long> marked(n + 2, 0);
	for (int i = 1; i < n + 1; i++) {
		if (graph[0][i] == 0 && graph[n + 1][i] == 0) {

			graph.push_back(graph[i]);
			marked[i] = graph.size() - 1;
			marked.push_back(i);

			graph[graph.size() - 1][i] = 1;
			std::fill(graph[i].begin(), graph[i].end(), 0);
			for (int j = 0; j < graph.size(); j++) {
				graph[j].push_back(0);
			}
			graph[i][graph.size() - 1] = 1;
		}
	}

	fout << FordFulkerson(graph, 0, n + 1);

	return 0;
}
