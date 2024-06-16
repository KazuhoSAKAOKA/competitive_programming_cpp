#include "pch.h"
#include "beam_search.hpp"
#include "point_2d.hpp"
#include <chrono>

using namespace competitive_programming;
using namespace competitive_programming::heuristic;
using namespace ::testing;

class game_board {
	const std::vector<std::vector<int>> points_;
	const int max_turn_;
public:
	game_board(std::vector<std::vector<int>>&& points, int max_turn) 
		: points_(std::move(points)), 
		max_turn_(max_turn){}
	size_t get_width() const { return points_.front().size(); }
	size_t get_height() const { return points_.size(); }
	int get_point(int y, int x) const {
		return points_[y][x];
	}
	int get_point(const point_int& p) const {
		return points_[p.get_y()][p.get_x()];
	}
	bool in_range(const point_int& p) const {
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

class test_state {

private:
	const game_board* board_;
	std::vector<point_int> history_;
	int score_;
public:
	test_state() :board_(nullptr), history_(), score_(0) {}
	test_state(const game_board* board, std::vector<point_int>&& history, int score = 0) :
		board_(board),
		history_(history),
		score_(score)
	{
	}
	test_state(const test_state&) = default;
	test_state& operator=(const test_state&) = default;

	std::vector<int> get_legal_actions() const {
		std::vector<int> actions;
		const auto& current = history_.back();
		actions.reserve(directions4.size());
		for (int i = 0; i < directions4.size(); i++) {
			const auto p = current + directions4[i];
			if (board_->in_range(p) && std::find(cbegin(history_), cend(history_), p) == cend(history_)) {
				actions.push_back(i);
			}
		}
		return actions;
	}
	test_state transit(int action)const {
		const auto& current = history_.back();
		const auto next = current + directions4[action];
		auto new_history(history_);
		new_history.emplace_back(next);
		const auto score = score_ + board_->get_point(next);
		return test_state(board_, std::move(new_history), score);
	}
	int get_score() const {
		return score_;
	}

	bool is_done() const {
		return history_.size() - 1 >= board_->get_max_turn();
	}


};


TEST(BeamSearchTest, SimpleTest)
{
	game_board board(
		{ 
			{1,1,1,1,1,100,},
			{3,1,1,1,1,1,  },
			{3,1,1,1,1,1,  },
			{3,1,1,1,1,1,  }, 
			{3,1,1,1,1,1,  },
		},
		5);

	test_state initial_state(&board, { point_int(0,0) });
	
	const auto ans1 = beam_search<test_state, int>(initial_state, 2, 5, std::chrono::minutes(10));
	EXPECT_EQ(3, ans1);

}
