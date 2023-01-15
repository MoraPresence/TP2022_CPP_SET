// Copyright 2022 mora

#include "help_for_tests.h"

class Set_Tests_Copy : public testing::Test {
	protected:
	std::set<int> std_set = {3, 3, -1, 6, 0, 0, 17, -5, 4, 2};
};

TEST_F(Set_Tests_Copy, Copy_by_Iterators) {
	Set<int> set(std_set.begin(),std_set.end());

	EXPECT_TRUE(set == std_set);
}

TEST_F(Set_Tests_Copy, Copy_by_Construct) {
	Set<int> set(std_set.begin(),std_set.end());
	Set<int> s2 = set;

	EXPECT_TRUE(s2 == std_set);
}

TEST_F(Set_Tests_Copy, Copy_SomeMagic) {
	Set<int> set(std_set.begin(), std_set.end());
	Set<int> s2 = { 1, 2, 3 };

	s2 = s2 = set;

	EXPECT_TRUE(s2 == std_set);
}
