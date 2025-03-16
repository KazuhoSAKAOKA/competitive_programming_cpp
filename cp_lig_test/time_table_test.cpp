#include "pch.h"
#include "time_table.hpp"

using namespace competitive_programming::heuristic;
using namespace ::testing;
using namespace std;


TEST(StateBaseTest, BasicTest)
{
	state_base<> a(1);
	state_base<> b(2);

	ASSERT_FALSE(a.exclusion(b));
	b.set(0, true);
	ASSERT_TRUE(a.exclusion(b));
}

TEST(StateBaseTest, AppendEraseTest)
{
	state_base<> a(4);
	state_base<> b(8);
	a.reserve(b);

	state_base<> c(4 | 8);
	
	ASSERT_EQ(a, c);
	a.release(b);

	state_base<> a_dash(4);
	ASSERT_EQ(a, a_dash);
}

TEST(VectorResourceTest, BasicTest)
{
	constexpr int MAX_TIME = 10000;
	using S = state_base<>;
	using R = vector_resource<S>;
	using B = state_duration<S>;

	R resource(MAX_TIME);
	constexpr size_t BAR_LENGTH = 5;
	B bar_0(S{ 1 }, BAR_LENGTH);

	ASSERT_TRUE(resource.placeable(bar_0, 0));
	resource.place(bar_0, 0);

	B bar_1(S{ 1 }, BAR_LENGTH);

	for (int i = 0; i < BAR_LENGTH; i++) {
		ASSERT_FALSE(resource.placeable(bar_1, i)) << "invalid:" <<i;
	}

	ASSERT_TRUE(resource.placeable(bar_1, BAR_LENGTH));

}
