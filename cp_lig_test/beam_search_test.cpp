#include "pch.h"
#include "beam_search.hpp"
#include "point_2d.hpp"
#include <chrono>
#include "test_utility.hpp"

using namespace competitive_programming;
using namespace competitive_programming::heuristic;
using namespace ::testing;

class beamsearch_test_state {

private:
	const game_board* board_;
	std::vector<point_int> history_;
	int score_;
public:
	beamsearch_test_state() :board_(nullptr), history_(), score_(0) {}
	beamsearch_test_state(const game_board* board, std::vector<point_int>&& history, int score = 0) :
		board_(board),
		history_(history),
		score_(score)
	{
	}
	beamsearch_test_state(const beamsearch_test_state&) = default;
	beamsearch_test_state& operator=(const beamsearch_test_state&) = default;

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
	beamsearch_test_state transit(int action)const {
		const auto& current = history_.back();
		const auto next = current + directions4[action];
		auto new_history(history_);
		new_history.emplace_back(next);
		const auto score = score_ + board_->get_point(next);
		return beamsearch_test_state(board_, std::move(new_history), score);
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
			{2,1,1,1,1,1,  },
			{2,1,1,1,1,1,  },
			{2,1,1,1,1,1,  }, 
			{2,1,1,1,1,1,  },
			{2,1,1,1,1,1,  },
		},
		5);

	beamsearch_test_state initial_state(&board, { point_int(0,0) });
	
	const auto ans1 = beam_search(initial_state, 20, 5, std::chrono::minutes(10));
	EXPECT_EQ(3, ans1);
	const auto ans2 = beam_search(initial_state, 2, 5, std::chrono::minutes(10));
	EXPECT_EQ(1, ans2);
}
