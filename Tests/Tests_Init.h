// Copyright 2022 mora

#include "help_for_tests.h"

TEST(set_init_tests, default_constructor) {
	Set<double> set;
	std::set<int> std_set  = { 1, 2, 3 };

	EXPECT_EQ(set.size(), 0);
}

TEST(set_init_tests, initialization_from_init_list) {
	Set<int> set = { 1, 2, 3 };
	std::set<int> std_set  = { 1, 2, 3 };

	EXPECT_TRUE(set == std_set);
}

TEST(set_init_tests, initialization_from_iterators) {
	std::vector initializer = { 1, 2, 3 };
	Set<int> set(initializer.begin(), initializer.end());
	std::set<int> std_set  = { 1, 2, 3 };

	EXPECT_EQ(set.size(), 3);
	EXPECT_TRUE(set == std_set);
}

TEST(set_init_tests, initialization_from_iterators_empty_vector) {
	std::vector<int> initializer;
	Set<int> set(initializer.begin(), initializer.end());
	std::set<int> std_set  = { 1, 2, 3 };

	EXPECT_EQ(set.size(), 0);
}

TEST(set_init_tests, initialization_copy_constructor) {
	std::vector<int> initializer = { 1, 2, 3};
	Set<int> set = { 1, 2, 3 };
	Set<int> copiedSet(set);
	std::set<int> std_set  = { 1, 2, 3 };

	EXPECT_TRUE(set == std_set);
	EXPECT_TRUE(copiedSet == std_set);

	copiedSet.insert(4);

	EXPECT_TRUE(set == std_set);
}
