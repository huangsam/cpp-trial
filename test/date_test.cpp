#include "../src/date.h"

#include <gtest/gtest.h>

class DateTest : public testing::Test {
 protected:
  Date one_date = Date(2024, 2, 1);
  Date newer_date = Date(2024, 2, 2);
  Date older_date = Date(2024, 1, 31);
};

TEST_F(DateTest, EqualComparisons) {
  ASSERT_EQ(one_date, one_date);
  ASSERT_LE(one_date, one_date);
  ASSERT_GE(one_date, one_date);
}

TEST_F(DateTest, LesserComparisons) {
  ASSERT_LT(one_date, newer_date);
  ASSERT_LE(one_date, newer_date);
}

TEST_F(DateTest, GreaterComparisons) {
  ASSERT_GT(one_date, older_date);
  ASSERT_GE(one_date, older_date);
}

TEST_F(DateTest, UnequalComparison) {
  ASSERT_NE(one_date, newer_date);
  ASSERT_NE(one_date, older_date);
}
