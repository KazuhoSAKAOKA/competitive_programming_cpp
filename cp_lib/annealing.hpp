#pragma once

#include <cmath>
#include <queue>
#include <chrono>
#include "time_keeper.hpp"

namespace competitive_programming::heuristic {

template <typename TState, typename TValue = long long>
TState hill_climb(const TState& state, int number, double start_temperature, double end_temperature) {
	constexpr auto INF = std::numeric_limits<TValue>::max();
	auto best_state(state);

	auto best_score = state.get_score();
	auto now_score = best_score;
	auto now_state(state);

	for (int i = 0; i < number; i++) {
		auto next_state = now_state.transition();
		auto next_score = next_state.get_score();


		const double temperature = start_temperature + (end_temperature - start_temperature) * (i / number);
		const double probability = exp((next_score - now_score) / temperature);
		const bool is_force_next = probability > (mt_for_action() % INF) / (double)INF;

		if (next_score > now_score || is_force_next) {
			now_score = next_score;
			now_state = next_state;
		}

		if (next_score > best_score) {
			best_score = best_score;
			best_state = next_state;
		}
	}
	return best_state;
}


}
