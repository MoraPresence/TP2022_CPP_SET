// Copyright 2022 mora

#include "Tests_by_Aleksei.h"
#include "Tests_Copy.h"
#include "Tests_Erase.h"
#include "Tests_Find.h"
#include "Tests_Init.h"
#include "Tests_Insert.h"
#include "Tests_Iterators.h"
#include "Tests_Lower_Bound.h"

#include <gtest/gtest.h>

int main() {
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}
