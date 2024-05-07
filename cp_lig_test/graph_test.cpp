#include "pch.h"

#include "graph.hpp"

using namespace competitive_programming;
using namespace ::testing;

TEST(GraphTest, DijkstraAdjacncyListTest) {
	adjacncy_list_graph<> g(10,
		{ 
			{1,0,1}, 
			{1,1,2},
			{1,2,3},
			{1,3,4},
			{1,4,5},
			{1,5,6},
			{1,6,7},
			{1,7,8},
			{1,8,9},
			{100,0,9},
		},
		true);

	const auto r = g.djikstra(0, 9);
	ASSERT_EQ(9, r);
}