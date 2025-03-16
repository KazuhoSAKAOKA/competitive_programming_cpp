#pragma once

#include <vector>
#include <map>
#include <bitset>
#include <algorithm>

namespace competitive_programming::heuristic {
constexpr size_t INFINITE = INT_MAX;

template<int N = 8>
class state_base {
	std::bitset<N> flags_;
public:
	state_base() :flags_() {}
	state_base(int bits) :flags_() {
		for (int i = 0; i < N; i++) {
			if ((1 << i) & bits) {
				flags_.set(i, true);
			}
		}
	}

	bool exclusion(const state_base& other) const {
		return (flags_ & other.flags_).any();
	}
	void set(int index, bool value) {
		flags_.set(index, value);
	}
	bool test(int index) const {
		return flags_.test(index);
	}

	void reserve(const state_base& other) {
		flags_ |= other.flags_;
	}

	void release(const state_base& other) {
		flags_ &= ~other.flags_;
	}

	bool operator==(const state_base& other) const {
		return flags_ == other.flags_;
	}
};

template<typename TState> 
class state_duration {
	TState state_;
	size_t duration_;
public:
	state_duration(int duration = INFINITE) :state_(), duration_(duration){
	}
	state_duration(const TState& state, size_t duration = INFINITE)
		:state_(state),
		duration_(duration)
	{
	}
	state_duration(TState&& state, size_t duration = INFINITE)
		:state_(std::move(state)),
		duration_(duration)
	{
	}
	const TState& get_state() const {
		return state_;
	}
	size_t get_duration() const {
		return duration_;
	}
	bool is_infinite() const {
		return duration_ == INFINITE;
	}
	int get_end_time(int start_time) const {
		if (is_infinite()) {
			return INFINITE;
		}
		return start_time + duration_;
	}
};


template<typename TState>
class vector_resource {
	std::vector<TState> states_;
	size_t last_index_ = 0;
public:
	using bar_t = state_duration<TState>;

	vector_resource(size_t size) : states_(size) {
	}
	
	bool placeable(const bar_t& bar, size_t start_time) const {
		const size_t end_index = bar.is_infinite() ? last_index_ : start_time + bar.get_duration();
		const auto& st = bar.get_state();
		return all_of(
			next(cbegin(states_), start_time),
			next(cbegin(states_), end_index),
				[&](const auto& a) {
					return !a.exclusion(st);
				});
	}

	void place(const bar_t& bar, size_t start_time, bool do_check = true) {
		if (do_check) {
			if (!placeable(bar, start_time)) {
				throw exception();
			}
		}
		const auto& st = bar.get_state();
		if (bar.is_infinite()) {
			states_[start_time].reserve(st);
			last_index_ = max(last_index_, start_time);
		}
		else {
			for (size_t i = 0; i < bar.get_duration(); i++) {
				states_[start_time + i].reserve(st);
			}
			last_index_ = max(last_index_, start_time + bar.get_duration());
		}
	}

	int find(const bar_t& bar, size_t start_time) const {

	}


};

template<typename TState>
class map_resource {
public:
	using bar_t = state_duration<TState>;

private:
	std::map<int, TState> states_;

public:

	bool placeable(const bar_t& bar, int start_time) const {
		if (states_.empty()) { return true; }
		const auto& st = bar.get_state();
		auto it = states_.lower_bound(start_time);
		while (it != cend(states_) {
			if (!bar.is_infinite()) {
				if (start_time + bar.get_duration() <= it->first) {
					break;
				}
			}
			if (it->second.exclusion(st)) {
				return false;
			}
			++it;
		}
		return true;
	}


	void reserve(const bar_t& bar, size_t start_time, bool do_check = true) {
		if (do_check) {
			if (!placeable(bar, start_time)) {
				throw exception();
			}
		}
		const auto& st = bar.get_state();
		auto it = states_.lower_bound(start_time);
		if (it == cend(states_) || it->first != start_time) {
			auto temp = states_.insert({ start_time, st });
			it = temp.first;
		}
		else{
			it->second.reserve(st);
		}
		++it;
		const auto end_limit = bar.get_end_time(start_time);
		while (it != cend(states_)) {
			if (end_limit < it->first) {

			}
		}
	}

	void release()
};

template<typename TState, typename TResource>
class time_table {
	std::vector<TResource> resources_;
};

}
