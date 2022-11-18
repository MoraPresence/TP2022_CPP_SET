// Copyright 2022 mora

#include "help_for_tests.h"

class Set_Tests_Erase : public testing::Test {
	protected:
	Set<int> set = {9, 8, 7, 6, 5, 4, 3, 2, 1};
};

TEST_F(Set_Tests_Erase, Erase_Element_From_Set) {
	EXPECT_EQ(*set.find(5), 5);

	set.erase(5);

	EXPECT_EQ(set.find(5), set.end());

	std::set<int> std_set = {1, 2, 3, 4, 6, 7, 8, 9};

	EXPECT_TRUE(set == std_set);
}

TEST_F(Set_Tests_Erase, Erase_All_Elements_From_Set) {
	std::vector<int> tmp = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	for (auto it: tmp) {
		set.erase(it);
	}

	EXPECT_EQ(set.empty(), true);
}

TEST_F(Set_Tests_Erase, Erase_NotExist_Element_From_Set) {
	EXPECT_EQ(set.size(), 9);
	set.erase(25);
	EXPECT_EQ(set.size(), 9);
}
