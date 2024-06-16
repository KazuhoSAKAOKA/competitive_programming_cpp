#pragma once

#include <cmath>


namespace competitive_programming::heuristic {


template <typename TState, typename TValue = long long>
TValue alpha_beta_score(
	const TState& state, 
	TValue alpha_score,
	TValue beta_score,
	int depth) {
	if (depth == 0 || state.is_done()) {
		return state.get_score();
	}
	const auto legal_actions = state.get_legal_actions();
	if (legal_actions.empty()) {
		return state.get_score();
	}
	for (auto&& action : legal_actions) {
		auto next_state = state.transit(action);
		auto score = -alpha_beta_score(next_state, -beta_score, -alpha_score, depth - 1);
		if (score > alpha_score) {
			alpha_score = score;
		}
		if(alpha_score >= beta_score){
			return alpha_score;
		}
	}
	return alpha_score;
}

template <typename TState, typename TValue = long long>
int alpha_beta(
	const TState& state,
	int depth) {
	auto best_action = -1;
	auto alpha_score = std::numeric_limits<TValue>::min() + 1;
	constexpr auto beta_score = std::numeric_limits<TValue>::max() - 1;
	const auto legal_actions = state.get_legal_actions();
	for (auto&& action : legal_actions) {
		auto next_state = state.transit(action);
		auto score = -alpha_beta_score(next_state, -beta_score, -alpha_score, depth);
		if (score > alpha_score) {
			best_action = action;
			alpha_score = score;
		}
	}
	return best_action;
}


}