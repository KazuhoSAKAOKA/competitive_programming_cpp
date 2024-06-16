#include "pch.h"
#include "hill_climb.hpp"
#include "annealing.hpp"
#include "test_utility.hpp"

using namespace competitive_programming::heuristic;
using namespace ::testing;
using namespace std;

class annealing_test_state :public test_state_base {

public:
	annealing_test_state(const game_board* game_board)
		: test_state_base(game_board)
	{

	}
};



TEST(HillClimbTest, SimpleTest)
{

}


