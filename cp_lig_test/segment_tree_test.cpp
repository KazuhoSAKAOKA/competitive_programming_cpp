#pragma once
#include "pch.h"
#include "segment_tree.hpp"

using namespace competitive_programming;
using namespace ::testing;

TEST(SegmentTreeTest, RMinQTest) 
{
	std::vector<long long> source{ 1,2,3,4,5,6,7,8, };
	seqment_tree_range_minimum_query<> st(source);
	
	auto get_expect = [&source](size_t a, size_t b) -> long long {
		long long min_value = LLONG_MAX;
		for (size_t i = a; i < b; i++) {
			min_value = std::min(min_value, source[i]);
		}
		return min_value;
		};

	for (size_t i = 0; i < source.size(); i++) {
		for (size_t j = i + 1; j <= source.size(); j++) {
			const auto expect = get_expect(i, j);
			const auto actual = st.query(i, j);
			ASSERT_EQ(expect, actual) << "(" << i << "," << j << ")";
		}
	}

	source[3] = 10;
	st.update(3, 10);

	for (size_t i = 0; i < source.size(); i++) {
		for (size_t j = i + 1; j <= source.size(); j++) {
			const auto expect = get_expect(i, j);
			const auto actual = st.query(i, j);
			ASSERT_EQ(expect, actual) << "(" << i << "," << j << ")";
		}
	}
}

TEST(SegmentTreeTest, RMaxQTest)
{
	std::vector<long long> source{ 1,2,3,4,5,6,7,8, };
	seqment_tree_range_maximum_query<> st(source);

	auto get_expect = [&source](size_t a, size_t b) -> long long {
		long long max_value = LLONG_MIN;
		for (size_t i = a; i < b; i++) {
			max_value = std::max(max_value, source[i]);
		}
		return max_value;
		};

	for (size_t i = 0; i < source.size(); i++) {
		for (size_t j = i + 1; j <= source.size(); j++) {
			const auto expect = get_expect(i, j);
			const auto actual = st.query(i, j);
			ASSERT_EQ(expect, actual) << "(" << i << "," << j << ")";
		}
	}

	source[3] = -1;
	st.update(3, -1);

	for (size_t i = 0; i < source.size(); i++) {
		for (size_t j = i + 1; j <= source.size(); j++) {
			const auto expect = get_expect(i, j);
			const auto actual = st.query(i, j);
			ASSERT_EQ(expect, actual) << "(" << i << "," << j << ")";
		}
	}
}

TEST(SegmentTree2DTest, RMinQTest)
{
	std::vector<std::vector<long long>> source
	{ 
		{1,2,3,4,5, 6, 7, 8, },
		{9,10,11,12,13,14,15,16,},
		{17,18,19,20,21, 22, 23, 24, },
		{25,26,27,28,29,30,31,32,},
	};

	auto get_expect = [&source](size_t y1, size_t x1, size_t y2, size_t x2) -> long long {
		long long min_value = LLONG_MAX;
		for (size_t i = y1; i < y2; i++) {
			for (size_t j = x1; j < x2; j++) {
				min_value = std::min(min_value, source[i][j]);
			}
		}
		return min_value;
		};

	seqment_tree_2d_range_minimum_query<> st(source);
	for (size_t i = 0; i < source.size(); i++) {
		for (size_t j = 0; j < source.front().size(); j++) {
			for (size_t iend = i + 1; iend < source.size(); iend++) {
				for (size_t jend = j + 1; jend < source.front().size(); jend++) {
					const auto expected = get_expect(i, j, iend, jend);
					const auto actual = st.query(i, j, iend, jend);
					ASSERT_EQ(expected, actual);
				}
			}
		}
	}

}

TEST(SegmentTree2DTest, RMinQTest2)
{
	std::vector<std::vector<long long>> source
	{
		{1,2,3,4,},
		{5, 6, 7, 8, },
		{9,10,11,12,},
		{13,14,15,16, },
		{17,18,19,20,},
		{21, 22, 23, 24, },
		{25,26,27,28,},
		{29,30,31,32, },
	};

	auto get_expect = [&source](size_t y1, size_t x1, size_t y2, size_t x2) -> long long {
		long long min_value = LLONG_MAX;
		for (size_t i = y1; i < y2; i++) {
			for (size_t j = x1; j < x2; j++) {
				min_value = std::min(min_value, source[i][j]);
			}
		}
		return min_value;
		};

	seqment_tree_2d_range_minimum_query<> st(source);
	for (size_t i = 0; i < source.size(); i++) {
		for (size_t j = 0; j < source.front().size(); j++) {
			for (size_t iend = i + 1; iend < source.size(); iend++) {
				for (size_t jend = j + 1; jend < source.front().size(); jend++) {
					const auto expected = get_expect(i, j, iend, jend);
					const auto actual = st.query(i, j, iend, jend);
					ASSERT_EQ(expected, actual);
				}
			}
		}
	}

}

