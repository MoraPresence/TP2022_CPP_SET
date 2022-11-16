// Copyright 2022 mora

#include <gtest/gtest.h>
#include "RBTree.h"

class RBTree_elementsTests : public testing::Test {
protected:
    void SetUp() override {
    }

};

TEST_F(RBTree_elementsTests, access_by_index_matrix) {
    RBTree<int> tree;

    tree.insert(12);

    tree.delete_node(12);

    EXPECT_TRUE(true);
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
