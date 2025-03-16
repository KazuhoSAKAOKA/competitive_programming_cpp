#pragma once

#include <queue>
#include <chrono>
#include "time_keeper.hpp"

namespace competitive_programming::heuristic {

/// <summary>
/// 
/// </summary>
/// <typeparam name="TState">TValue TState::get_score() const ,TState transit(int)const, Container get_legal_actions() const </typeparam>
/// <typeparam name="TValue"></typeparam>
/// <param name="state"></param>
/// <param name="beam_width"></param>
/// <param name="beam_depth"></param>
/// <param name="duration"></param>
/// <returns></returns>
template <typename TState, typename TValue = long long>
int beam_search(const TState& state,
	int beam_width, 
	int beam_depth, 
	const std::chrono::high_resolution_clock::duration& duration) {

	struct bs_state {
		TState state_;
		int first_select_;
		bool operator< (const bs_state& other) const {
			return state_.get_score() < other.state_.get_score();
		}
	};
	using PQ = std::priority_queue<bs_state>;
	PQ current_beam_queue;
	bs_state best_state{ state , -1 };
	current_beam_queue.push(best_state);
	time_keeper tk(duration);
	for (int depth = 0; depth < beam_depth; depth++) {
		PQ next_beam_queue;
		for (int i = 0; i < beam_width; i++) {
			if (tk.is_overtime()) {
				if (best_state.first_select_ < 0) {
					return state.get_legal_actions()[0];
				}
				return best_state.first_select_;
			}

			if (current_beam_queue.empty()) {
				break;
			}
			const bs_state current_state = current_beam_queue.top();
			current_beam_queue.pop();
			const auto legal_actions = current_state.state_.get_legal_actions();
			for (auto&& action : legal_actions) {
				next_beam_queue.push(bs_state{ 
					current_state.state_.transit(action), 
					depth == 0 ? action : current_state.first_select_
					});
			}
		}
		current_beam_queue = std::move(next_beam_queue);

		best_state = current_beam_queue.top();
		if (best_state.state_.is_done()) {
			break;
		}
	}

	return best_state.first_select_;
}


/// <summary>
/// 
/// </summary>
/// <typeparam name="TState">TValue TState::get_score() const ,TState transit(TAction)const, Container<TAction> get_legal_actions() const </typeparam>
/// <typeparam name="TValue"></typeparam>
/// <param name="state"></param>
/// <param name="beam_width"></param>
/// <param name="beam_depth"></param>
/// <param name="duration"></param>
/// <returns></returns>
template <typename TState, typename TAction, typename TValue = long long>
TAction beam_search(const TState& state,
	int beam_width,
	int beam_depth,
	const std::chrono::high_resolution_clock::duration& duration) {

	struct bs_state {
		TState state_;
		optional<TAction> first_select_;
		bool operator< (const bs_state& other) const {
			return state_.get_score() < other.state_.get_score();
		}
	};
	using PQ = std::priority_queue<bs_state>;
	PQ current_beam_queue;
	bs_state best_state{ state , nullopt };
	current_beam_queue.push(best_state);
	time_keeper tk(duration);
	for (int depth = 0; depth < beam_depth; depth++) {
		PQ next_beam_queue;
		for (int i = 0; i < beam_width; i++) {
			if (tk.is_overtime()) {
				if (!best_state.first_select_.has_value()) {
					return state.get_legal_actions()[0];
				}
				return best_state.first_select_.value();
			}

			if (current_beam_queue.empty()) {
				break;
			}
			const bs_state current_state = current_beam_queue.top();
			current_beam_queue.pop();
			const auto legal_actions = current_state.state_.get_legal_actions();
			for (auto&& action : legal_actions) {
				next_beam_queue.push(bs_state{
					current_state.state_.transit(action),
					depth == 0 ? action : current_state.first_select_
					});
			}
		}
		current_beam_queue = std::move(next_beam_queue);

		best_state = current_beam_queue.top();
		if (best_state.state_.is_done()) {
			break;
		}
	}

	return best_state.first_select_.value();
}


}