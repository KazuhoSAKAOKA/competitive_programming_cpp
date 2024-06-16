#include "pch.h"
#include "alpha_beta.hpp"
#include <set>
#include <algorithm>

using namespace competitive_programming::heuristic;
using namespace ::testing;
using namespace std;

constexpr int BOARD_SIZE = 3;
class ttt {
	enum class ox {
		none,
		o,
		x,
	};
	vector<vector<ox>> board_;
	int turn_ = 0;
	int last_action_ = -1;

	int connected_length(int y,int x, int dy, int dx, ox value) const {
		if (y < 0 || BOARD_SIZE <= y || x < 0 || BOARD_SIZE <= x) {
			return 0;
		}
		if (board_[y][x] != value) {
			return 0;
		}
		return 1 + connected_length(y + dy, x + dx, dy, dx, value);
	}

public:
	ttt():board_(BOARD_SIZE, vector<ox>(BOARD_SIZE, ox::none)){}
	ttt(const ttt&) = default;
	ttt& operator=(const ttt&) = default;

	vector<int> get_legal_actions() const {
		vector<int> actions;
		for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
			if (board_[i / BOARD_SIZE][i % BOARD_SIZE] == ox::none) {
				actions.push_back(i);
			}
		}
		return actions;
	}

	ttt transit(int action) const {
		if (action < 0 || BOARD_SIZE * BOARD_SIZE <= action) {
			throw std::exception("transit failure, out of range");
		}
		if (is_done()) {
			throw std::exception("transit failure, end of game");
		}
		const auto y = action / BOARD_SIZE;
		const auto x = action % BOARD_SIZE;
		if (board_[y][x] != ox::none) {
			throw std::exception("transit failure, exist other");
		}
		auto next_state = ttt(*this);
		next_state.board_[y][x] = turn_ % 2 == 0 ? ox::o : ox::x;
		next_state.turn_ = turn_ + 1;
		next_state.last_action_ = action;
		return next_state;
	}

	bool is_done() const {
		if (turn_ == 9) { return true; }
		if (last_action_ < 0) { return false; }
		const auto v = turn_ % 2 == 1 ? ox::o : ox::x;

		const int y = last_action_ / BOARD_SIZE;
		const int x = last_action_ % BOARD_SIZE;

		if (
			(connected_length(y, x, 0, -1, v) + connected_length(y, x + 1, 0, 1, v) == BOARD_SIZE) ||
			(connected_length(y, x, -1, 0, v) + connected_length(y + 1, x, 1, 0, v) == BOARD_SIZE) ||
			(connected_length(y, x, -1, -1, v) + connected_length(y + 1, x + 1, 1, 1, v) == BOARD_SIZE) ||
			(connected_length(y, x, 1, -1, v) + connected_length(y - 1, x + 1, -1, 1, v) == BOARD_SIZE)
			) {
			return true;
		}
		return false;
	}

	int get_score() const {
		if (turn_ == 9) { return 0; }
		if (is_done()) {
			return -1;
		}
		return 0;
	}
};

TEST(AlphaBetaTest, TttTest) {
	ttt state;
	const auto step1 = state.transit(4);
	// 初手が中央に打たれた場合後手は四隅のどれかを打たなければだめ
	const auto action2 = alpha_beta(step1, 9);
	const set<int> e1{0,2,6,8};
	EXPECT_TRUE(e1.count(action2) == 1);
	
	const auto step2 = step1.transit(0);
	const auto step3 = step2.transit(2);

	// リーチ
	const auto action4 = alpha_beta(step3, 9);
	EXPECT_EQ(6, action4);
	const auto step4 = step3.transit(action4);

	//リーチ
	const auto action5 = alpha_beta(step4, 9);
	EXPECT_EQ(3, action5);
}

