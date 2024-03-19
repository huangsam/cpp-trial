#include "../src/lambda.h"

#include <gtest/gtest.h>

#include <list>

TEST(LambdaTest, LessThanComparison) {
  EXPECT_EQ(lessThan(3, 3), false);
  EXPECT_EQ(lessThan(3, 4), true);
  EXPECT_EQ(lessThan(-4, -3), true);
}

TEST(LambdaTest, SumOfSquares) {
  EXPECT_EQ(sumOfSquares(std::list{1, 1, 1}), 3);
  EXPECT_EQ(sumOfSquares(std::list{1, 2, 3}), 1 + 4 + 9);
}
