#pragma once
#include <vector>
#include "point_2d.hpp"

class game_board {
	const std::vector<std::vector<int>> points_;
	const int max_turn_;
public:
	game_board(std::vector<std::vector<int>>&& points, int max_turn)
		: points_(std::move(points)),
		max_turn_(max_turn) {}
	size_t get_width() const { return points_.front().size(); }
	size_t get_height() const { return points_.size(); }
	int get_point(int y, int x) const {
		return points_[y][x];
	}
	int get_point(const competitive_programming::point_int& p) const {
		return points_[p.get_y()][p.get_x()];
	}
	bool in_range(const competitive_programming::point_int& p) const {
		const auto x = p.get_x();
		const auto y = p.get_y();
		return
			0 <= y && y < points_.size() &&
			0 <= x && x < points_[y].size();
	}
	int get_max_turn() const {
		return max_turn_;
	}
};

class test_state_base {
	const game_board* game_board_;

public:
	test_state_base(const game_board* game_board = nullptr) : game_board_(game_board) {}
	test_state_base(const test_state_base&) = default;
	test_state_base(test_state_base&&) = default;
	test_state_base& operator=(const test_state_base&) = default;
	test_state_base& operator=(test_state_base&&) = default;
	int get_point(int y, int x) const {
		if (game_board_ == nullptr) { throw std::exception(); }
		return game_board_->get_point(y,x);
	}
	int get_point(const competitive_programming::point_int& p) const {
		if (game_board_ == nullptr) { throw std::exception(); }
		return game_board_->get_point(p);
	}
	bool in_range(const competitive_programming::point_int& p) const {
		if (game_board_ == nullptr) { throw std::exception(); }
		return game_board_->in_range(p);
	}
};
