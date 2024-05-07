#pragma once
#include <vector>
#include <queue>
#include <numeric>

namespace competitive_programming {

template <typename T = long long>
struct edge {
	T cost_;
	size_t from_;
	size_t to_;
};


template <typename T = long long>
struct adjacncy_matrix_graph {

	std::vector<std::vector<T>> graph_;

	static T djikstra(const std::vector<std::vector<T>>& graph, size_t s, size_t e) {
		std::vector<T> costs(graph.size(), std::numeric_limits<T>::max());
		struct point {
			T cost;
			size_t pos;
			bool operator < (const point& other) const {
				return cost < other.cost;
			}
		};
		std::priority_queue<point> p_queue;
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
			bool operator < (const point& other) const {
				return cost < other.cost;
			}
		};
		std::priority_queue<point> p_queue;
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
};


}