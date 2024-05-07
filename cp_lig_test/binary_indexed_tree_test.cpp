#include "pch.h"

#include "binary_indexed_tree.hpp"

using namespace competitive_programming;
using namespace ::testing;


TEST(BITTest, SimpleTest) {
	constexpr size_t N = 100;
	fenwick_tree bit(N);

	for (int i = 0; i < N; i++) {
		bit.add(i, i + 1);
	}

	ASSERT_EQ(1, bit.get(0));
	ASSERT_EQ((N + 1) * N / 2, bit.get(N - 1));
	for (int i = 1; i < N; i++) {
		ASSERT_EQ(i + 1, bit.get(i - 1, i));
	}
}