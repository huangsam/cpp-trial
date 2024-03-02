#include <gtest/gtest.h>

#include "../src/factorial.h"

TEST(FactorialTest, BasicAssertions) {
  EXPECT_EQ(factorial(0), 1);
  EXPECT_EQ(factorial(1), 1);
  EXPECT_EQ(factorial(2), 2);
  EXPECT_EQ(factorial(3), 6);
  EXPECT_EQ(factorial(4), 24);
}
