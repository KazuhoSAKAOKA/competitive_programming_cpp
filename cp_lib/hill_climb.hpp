#pragma once


#include <queue>
#include <chrono>
#include "time_keeper.hpp"

namespace competitive_programming::heuristic {

template <typename TState, typename TValue = long long>
TState hill_climb(const TState& state, int number) {
	auto best_state(state);
	auto best_score = state.get_score();
	for (int i = 0; i < number; i++) {
		auto next_state = next_state.transition();
		auto next_score = next_state.get_score();
		if (next_score > best_score) {
			best_score = next_score;
			best_state = next_state;
		}
	}
	return best_state;
}


}
