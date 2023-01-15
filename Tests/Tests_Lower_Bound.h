// Copyright 2022 mora

#include "help_for_tests.h"

class Set_Tests_Lower_Bound : public testing::Test {
	protected:
	Set<double> set = {2, 4, 6, 8, 10, 12, 14, 16, 18};
};

TEST_F(Set_Tests_Lower_Bound, existingBound) {
	std::vector<int> bound = {1, 3, 5, 7, 9, 11, 13, 15, 17};
	for (auto iter: bound) {
		EXPECT_EQ(*set.lower_bound(iter), iter + 1);
	}
}

TEST_F(Set_Tests_Lower_Bound, unexistingBound) {
	EXPECT_EQ(set.lower_bound(105), set.end());
}
