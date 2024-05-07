#include "pch.h"

#include "union_find.hpp"

using namespace competitive_programming;
using namespace ::testing;

TEST(UnionFineTest, SimpleTest) {

	constexpr size_t N = 100;
	union_find uf(N);

	uf.unite(0, 1);
	uf.unite(1, 2);
	ASSERT_TRUE(uf.same(0, 1)) << "����O���[�v�łȂ���΂Ȃ�Ȃ�";
	ASSERT_TRUE(uf.same(1, 2)) << "����O���[�v�łȂ���΂Ȃ�Ȃ�";
	ASSERT_TRUE(uf.same(0, 2)) << "����O���[�v�łȂ���΂Ȃ�Ȃ�";
	ASSERT_FALSE(uf.same(0, 3)) << "�Ⴄ�O���[�v�łȂ���΂Ȃ�Ȃ�";
	ASSERT_EQ(3, uf.size(0)) << "�T�C�Y�m�F";
	ASSERT_EQ(3, uf.size(1)) << "�T�C�Y�m�F";
	ASSERT_EQ(3, uf.size(2)) << "�T�C�Y�m�F";
}

TEST(UnionFineTest, EquilibriumTest) {

	constexpr size_t N = 100;
	union_find uf(N);

	uf.unite(1, 2);
	uf.unite(2, 3);
	uf.unite(3, 4);
	uf.unite(4, 5);
	uf.unite(5, 6);

	uf.unite(11, 12);

	uf.unite(6, 12);

	ASSERT_TRUE(uf.same(11, 1)) << "�����O���[�v";
	ASSERT_EQ(1, uf.root(11)) << "�T�C�Y���傫���O���[�v���̃��[�g�������O���[�v�̃��[�g";
	ASSERT_EQ(8, uf.size(6)) << "�T�C�Y�m�F";
	ASSERT_EQ(8, uf.size(12)) << "�T�C�Y�m�F";
}

TEST(UnionFineTest, EquilibriumRevTest) {

	constexpr size_t N = 100;
	union_find uf(N);

	uf.unite(1, 2);

	uf.unite(11, 12);
	uf.unite(12, 13);
	uf.unite(13, 14);
	uf.unite(14, 15);
	uf.unite(15, 16);

	uf.unite(2, 16);

	ASSERT_TRUE(uf.same(1, 11)) << "�����O���[�v";
	ASSERT_EQ(11, uf.root(11)) << "�T�C�Y���傫���O���[�v���̃��[�g�������O���[�v�̃��[�g";
	ASSERT_EQ(8, uf.size(2)) << "�T�C�Y�m�F";
	ASSERT_EQ(8, uf.size(12)) << "�T�C�Y�m�F";
}
