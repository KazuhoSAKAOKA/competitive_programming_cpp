#pragma once
#include <chrono>

namespace competitive_programming::heuristic {

	struct time_keeper {
		const std::chrono::high_resolution_clock::time_point limit_;
		time_keeper(const std::chrono::high_resolution_clock::duration& duration) 
			: limit_(std::chrono::high_resolution_clock::now() + duration){
		}
		bool is_overtime() const {
			return limit_ < std::chrono::high_resolution_clock::now();
		}
	};

}