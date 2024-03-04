#include "../src/date.h"

#include <gtest/gtest.h>

class DateTest : public testing::Test {
 protected:
  Date one_date = Date(2024, 2, 1);
};

TEST_F(DateTest, EqualComparisons) {
  ASSERT_EQ(one_date, one_date);
  ASSERT_LE(one_date, one_date);
  ASSERT_GE(one_date, one_date);
}

TEST_F(DateTest, LesserComparisons) {
  Date newer_date = Date(2024, 2, 2);
  ASSERT_LT(one_date, newer_date);
  ASSERT_LE(one_date, newer_date);
}

TEST_F(DateTest, GreaterComparisons) {
  Date older_date = Date(2024, 1, 31);
  ASSERT_GT(one_date, older_date);
  ASSERT_GE(one_date, older_date);
}
