// Copyright 2022 mora

#include "help_for_tests.h"

class Set_Tests_Find : public testing::Test {
	protected:
	Set<int> set = {1, 2, 3, 4, 5, 6, 7, 8, 9};
};

TEST_F(Set_Tests_Find, Find_All_Elements) {
	std::vector<int> tmp = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	for (auto iter: tmp) {
		EXPECT_EQ(*set.find(iter), iter);
	}
}

TEST_F(Set_Tests_Find, Find_Elements_After_Insert) {
	set.insert(10);
	set.insert(11);

	EXPECT_EQ(*set.find(10), 10);
	EXPECT_EQ(*set.find(11), 11);
	EXPECT_EQ(*set.find(1), 1);
}

TEST_F(Set_Tests_Find, Find_Elements_NotExist) {
	EXPECT_EQ(set.find(10), set.end());
}
