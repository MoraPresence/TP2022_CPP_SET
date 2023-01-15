// Copyright 2022 mora

#include "help_for_tests.h"

TEST(set_insert_tests, Insert_without_Balance) {
	Set<int> set = Set<int>();
	set.insert(4);
	set.insert(3);
	set.insert(6);

	std::set<int> std_set  = { 4, 3, 6 };

	EXPECT_TRUE(set == std_set);
}

TEST(set_insert_tests, Insert_with_TurnLeft) {
	Set<int> set;
	set.insert(2);
	set.insert(3);
	set.insert(5);

	std::set<int> std_set  = { 2, 3, 5 };

	EXPECT_TRUE(set == std_set);
}

TEST(set_insert_tests, Insert_with_TurnRight) {
	Set<int> set;
	set.insert(3);
	set.insert(2);
	set.insert(1);

	std::set<int> std_set  = { 3, 2, 1 };

	EXPECT_TRUE(set == std_set);
}

TEST(set_insert_tests, Insert_Existing) {
	Set<int> set;
	set.insert(3);
	set.insert(2);
	set.insert(1);
	set.insert(1);

	std::set<int> std_set  = { 3, 2, 1 };

	EXPECT_TRUE(set == std_set);
}
