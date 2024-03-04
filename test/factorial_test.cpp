#include "../src/factorial.h"

#include <gtest/gtest.h>

TEST(FactorialTest, TextbookInputs) {
  // 0 is the smallest valid input
  EXPECT_EQ(factorial(0), 1);

  // 1..n are valid inputs
  EXPECT_EQ(factorial(1), 1);
  EXPECT_EQ(factorial(2), 2);
  EXPECT_EQ(factorial(3), 6);
  EXPECT_EQ(factorial(4), 24);
}

TEST(FactorialTest, OutOfBounds) {
  // -1 and below are invalid inputs
  EXPECT_ANY_THROW(factorial(-1));
}
