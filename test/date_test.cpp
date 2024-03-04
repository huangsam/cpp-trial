#include "../src/date.h"

#include <gtest/gtest.h>

TEST(DateTest, EqualityComparisons) {
  Date one_date = Date(2024, 2, 1);
  ASSERT_EQ(one_date, one_date);
  ASSERT_LE(one_date, one_date);
  ASSERT_GE(one_date, one_date);
}

TEST(DateTest, InequalityComparisons) {
  Date one_date = Date(2024, 2, 1);
  Date newer_date = Date(2024, 2, 2);
  Date older_date = Date(2024, 1, 31);
  ASSERT_LT(one_date, newer_date);
  ASSERT_LE(one_date, newer_date);
  ASSERT_GT(one_date, older_date);
  ASSERT_GE(one_date, older_date);
}
