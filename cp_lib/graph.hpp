#pragma once
#include <vector>
#include <queue>
#include <numeric>
#include <algorithm>
#include "union_find.hpp"

namespace competitive_programming {

template <typename T = long long>
struct edge {
	T cost_;
	size_t from_;
	size_t to_;
};

template <typename T = long long>
static T kruskal(size_t n, std::vector<edge<T>>& edges, size_t s = 0) {
	sort(begin(edges), end(edges), [](const auto& a, const auto& b) { return a.cost_ < b.cost_; });
	union_find uf(n);
	T result = 0;
	for (auto&& edge : edges) {
		if (!uf.same(edge.from_, edge.to_)) {
			uf.unite(edge.from_, edge.to_);
			result += edge.cost_;
		}
	}
	return result;
}

template <typename T = long long>
static T bellman_ford(size_t n, const std::vector<edge<T>>& edges, size_t s, size_t e) {
	constexpr T INF = std::numeric_limits<T>::max();
	vector<T> costs(n, INF);
	costs[s] = 0;

	size_t loop_counter = 0;
	bool updated = true;
	while (updated) {
		updated = false;
		for (auto&& edge : edges) {
			if (costs[edge.from_] != INF && costs[edge.to_] > costs[edge.from_] + edge.cost_) {
				costs[edge.to_] = costs[edge.from_] + edge.cost_;
				updated = true;
			}
		}
		loop_counter++;
	}

	return costs[e];
}


template <typename T = long long>
struct adjacncy_matrix_graph {

	std::vector<std::vector<T>> graph_;

	static T djikstra(const std::vector<std::vector<T>>& graph, size_t s, size_t e) {
		std::vector<T> costs(graph.size(), std::numeric_limits<T>::max());
		struct point {
			T cost;
			size_t pos;
			bool operator > (const point& other) const {
				return cost > other.cost;
			}
		};
		std::priority_queue<point, std::vector<point>, std::greater<point>> p_queue;
		p_queue.push(point{ 0, s });
		costs[s] = 0;

		while (!p_queue.empty()) {
			const auto [current_cost, current] = p_queue.top();
			p_queue.pop();
			if (costs[current] < current_cost) { continue; }
			for (int i = 0; i < graph.size(); i++) {
				if (graph[current][i] != 0) {
					if (costs[i] > graph[current][i] + current_cost) {
						costs[i] = graph[current][i] + current_cost;
						p_queue.push(point{ costs[i] , i });
					}
				}
			}
		}
		return costs[e];
	}

	static void warshall_floyd(std::vector<std::vector<T>>& dist) {
		for (int k = 0; k < V; k++) {
			for (int i = 0; i < V; i++) {
				for (int j = 0; j < V; j++) {
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
				}
			}
		}
	}

};



template <typename T = long long>
struct adjacncy_list_graph {
	struct outbound_edge {
		T cost_;
		size_t to_;
	};
	std::vector<std::vector<outbound_edge>> graph_;

	adjacncy_list_graph(size_t n, std::initializer_list<edge<T>> edges, bool undirected) : graph_(n, std::vector<outbound_edge>()) {
		for (auto&& e : edges) {
			graph_[e.from_].emplace_back(outbound_edge{e.cost_, e.to_});
			if (undirected) {
				graph_[e.to_].emplace_back(outbound_edge{ e.cost_, e.from_ });
			}
		}
	}

	operator const std::vector<std::vector<outbound_edge>>&() const {
		return graph_;
	}

	static T djikstra(const std::vector<std::vector<outbound_edge>>& graph, size_t s, size_t e) {
		std::vector<T> costs(graph.size(), std::numeric_limits<T>::max());
		struct point {
			T cost;
			size_t pos;
			bool operator > (const point& other) const {
				return cost > other.cost;
			}
		};
		std::priority_queue<point, std::vector<point>, std::greater<point>> p_queue;
		p_queue.push(point{ 0, s });
		costs[s] = 0;
		while (!p_queue.empty()) {
			const auto [current_cost, current] = p_queue.top();
			p_queue.pop();
			if (costs[current] < current_cost) { continue; }
			for (auto&& [cost, to] : graph[current]) {
				if (costs[to] > cost + current_cost) {
					costs[to] = cost + current_cost;
					p_queue.push(point{ costs[to] , to });
				}
			}
		}
		return costs[e];
	}



	T djikstra(size_t s, size_t e) const {
		return djikstra(graph_, s, e);
	}


	static T prim(const std::vector<std::vector<outbound_edge>>& graph, size_t s = 0) {
		std::vector<T> min_costs(graph.size(), std::numeric_limits<T>::max());
		std::vector<bool> connected(graph.size(), false);
		struct point {
			T cost;
			size_t pos;
			bool operator > (const point& other) const {
				return cost > other.cost;
			}
		};
		T res = 0;
		std::priority_queue<point, std::vector<point>, std::greater<point>> p_queue;
		p_queue.push(point{ 0, s });
		min_costs[s] = 0;
		while (!p_queue.empty()) {
			const auto [_, current] = p_queue.top();
			p_queue.pop();
			if (connected[current]) { continue; }
			res += min_costs[current];
			connected[current] = true;

			for (auto&& [cost, to] : graph[current]) {
				if (!connected[to]) {
					min_costs[to] = min(min_costs[to], cost);
					p_queue.push(point{ min_costs[to] , to });
				}
			}
		}
		return res;
	}

	T prim(size_t s = 0) const {
		return prim(graph_, s);
	}


};


using graph_t = std::vector<std::vector<int>>;
static std::vector<int> topo_sort(const graph_t& G) {  // bfs
	std::vector<int> ans;
	int n = (int)G.size();
	std::vector<int> ind(n);            // ind[i]: í∏ì_iÇ…ì¸ÇÈï”ÇÃêî(éüêî)
	for (int i = 0; i < n; i++) {  // éüêîÇêîÇ¶ÇƒÇ®Ç≠
		for (auto e : G[i]) {
			ind[e]++;
		}
	}
	std::queue<int> que;
	for (int i = 0; i < n; i++) {  // éüêîÇ™0ÇÃì_ÇÉLÉÖÅ[Ç…ì¸ÇÍÇÈ
		if (ind[i] == 0) {
			que.push(i);
		}
	}
	while (!que.empty()) {  // ïùóDêÊíTçı
		int now = que.front();
		ans.push_back(now);
		que.pop();
		for (auto e : G[now]) {
			ind[e]--;
			if (ind[e] == 0) {
				que.push(e);
			}
		}
	}
	return ans;
}

}