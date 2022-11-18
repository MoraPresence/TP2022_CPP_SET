// Copyright 2022 mora

#include "help_for_tests.h"

class Set_Tests_Iterators : public testing::Test {
	protected:
	Set<int> empty_set;
	Set<int> set = { 3, 3, -1, 6, 0, 0, 17, -5, 4, 2 };
	std::set<int> std_set = { 3, 3, -1, 6, 0, 0, 17, -5, 4, 2 };
};

TEST_F(Set_Tests_Iterators, Empty_Iterators) { EXPECT_EQ(empty_set.begin(), empty_set.end()); }

TEST_F(Set_Tests_Iterators, Erase_and_Check_Iterators) {
	for (auto it : std_set) {
		set.erase(it);
	}

	EXPECT_EQ(set.begin(), set.end());
}

TEST_F(Set_Tests_Iterators, Forward_Iteration) {
	auto it_std_set = std_set.begin();

	for (auto it : set) {
		EXPECT_EQ(*it_std_set, it);
		++it_std_set;
	}
}
