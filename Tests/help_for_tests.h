// Copyright 2022 mora

#pragma once

#include "Set.h"

#include <gtest/gtest.h>

template <typename Key> bool operator==(Set<Key>& lhs, std::set<Key>& rhs) {
	auto itIn = lhs.begin();
	auto itOut = rhs.begin();
	for (; itIn != lhs.end() || itOut != rhs.end(); ++itIn, ++itOut) {
		if (*itIn != *itOut) {
			return false;
		}
	}
	return true;
}
