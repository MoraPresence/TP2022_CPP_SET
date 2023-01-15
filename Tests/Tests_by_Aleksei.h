// Copyright 2022 mora

#include "Set.h"

#include <gtest/gtest.h>

TEST(HalaidzhiTests, check_constness) {
	const Set<int> s{-4, 5, 3, 0, 7};

	EXPECT_NE(s.find(3), s.end());

	EXPECT_EQ(*s.lower_bound(2), 3);
	EXPECT_EQ(s.lower_bound(8), s.end());
	EXPECT_EQ(*s.lower_bound(-2), 0);

	EXPECT_EQ(s.empty(), false);
	EXPECT_EQ(s.size(), 5);

	auto first = s.begin();
	auto last = s.end();
	EXPECT_EQ(*first, -4);
	EXPECT_EQ(*(--last), 7);
}

TEST(HalaidzhiTests, check_copy_correctness) {
	int elems[] = {3, 3, -1, 6, 0, 0, 17, -5, 4, 2};
	Set<int> s1(elems, elems + 10);
	std::set<int> set_elems(elems, elems + 10);
	Set<int> s2 = s1;
	s2.insert(5);
	s2.insert(18);
	s2.insert(-2);
	auto s1_it = s1.begin(), s2_it = s2.begin();
	auto s_it = set_elems.begin();
	while (s1_it != s1.end() || s2_it != s2.end() || s_it != set_elems.end()) {
		if (*s2_it == 5 || *s2_it == 18 || *s2_it == -2) {
			++s2_it;
			continue;
		}

		EXPECT_EQ(*s1_it, *s2_it);
		EXPECT_EQ(*s1_it, *s_it);
		EXPECT_EQ(*s2_it, *s_it);

		++s1_it, ++s2_it, ++s_it;
	}

	s1 = s2;
	s2.insert(19);
	auto cur_end = s2.end();
	cur_end--;
	s1_it = s1.begin(), s2_it = s2.begin();
	while (s1_it != s1.end() || s2_it != cur_end) {
		EXPECT_EQ(*s1_it, *s2_it);
		++s1_it, ++s2_it;
	}

	s1 = s1 = s2;
	s1_it = s1.begin(), s2_it = s2.begin();
	while (s1_it != s1.end() || s2_it != s2.end()) {
		EXPECT_EQ(*s1_it, *s2_it);
		++s1_it, ++s2_it;
	}
}

TEST(HalaidzhiTests, check_iterators) {
	Set <std::pair<int, int>> s{{-3, 5},
		{5,  5},
		{-4, 1},
		{-4, 4},
		{0,  1},
		{3,  0}};
	EXPECT_EQ(s.begin()->second, 1);
	EXPECT_EQ((++s.begin())->first, -4);

	auto cur = s.end();
	Set<int> small{1};
	auto it = small.begin();
	EXPECT_EQ(*it, 1);
	auto begin = s.begin();
	begin++;
	cur--;
	EXPECT_NE(begin, cur);

	while (begin != cur) {
		++begin;
		--cur;
	}
	EXPECT_EQ(*begin, *cur);
}

struct StrangeInt {
	int x;
	static int counter;

	StrangeInt() {
		++counter;
	}

	StrangeInt(int _x) : x(_x) {
		++counter;
	}

	StrangeInt(const StrangeInt &rs) : x(rs.x) {
		++counter;
	}

	bool operator<(const StrangeInt &rs) const {
		return x < rs.x;
	}

	static void init() {
		counter = 0;
	}

	~StrangeInt() {
		--counter;
	}

	friend std::ostream &operator<<(std::ostream &out, const StrangeInt &_x) {
		out << _x.x;
		return out;
	}
};

int StrangeInt::counter;

TEST(HalaidzhiTests, check_operator_less) {
	Set <StrangeInt> s{-5, -3, -6, 13, 7, 1000, 963};
	auto it = s.lower_bound(999);
	++it;
	EXPECT_EQ(it, s.end());
}

TEST(HalaidzhiTests, check_destructor) {
	StrangeInt::init();
	{
		Set <StrangeInt> s{5, 4, 3, 2, 1, 0};
		EXPECT_EQ(s.size(), 6);
	}
	EXPECT_EQ(StrangeInt::counter, 0);
	{
		Set <StrangeInt> s{-3, 3, -2, 2, -1, 1};
		Set <StrangeInt> s1(s);
		s1.insert(0);
		Set <StrangeInt> s2(s1);
		EXPECT_NE(s1.find(0), s1.end());
		s1 = s;
		EXPECT_EQ(s1.find(0), s1.end());
	}
	EXPECT_EQ(StrangeInt::counter, 0);
}

/* check erase for correctness */
TEST(HalaidzhiTests,  check_erase) {

	Set <std::string> s{"abacaba", "hello", "p"};
	s.erase("miss");
	s.erase("hello");
	EXPECT_EQ(s.size(), 2);
	s.erase("p");
	EXPECT_EQ(*s.begin(), "abacaba");
	s.erase("1");
	s.erase("abacaba");
	s.erase("012");
	EXPECT_EQ(s.empty(), true);
}
