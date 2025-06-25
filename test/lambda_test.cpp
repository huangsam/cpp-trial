#include "../src/lambda.h"

#include <gtest/gtest.h>

#include <vector>

TEST(LambdaTest, LessThanComparison) {
  EXPECT_EQ(less_than(ValueOne(3), ValueTwo(3)), false);
  EXPECT_EQ(less_than(ValueOne(3), ValueTwo(4)), true);
  EXPECT_EQ(less_than(ValueOne(-4), ValueTwo(-3)), true);
}

TEST(LambdaTest, SumOfSquares) {
  EXPECT_EQ(sum_of_squares(std::vector{1, 1, 1}), 3);
  EXPECT_EQ(sum_of_squares(std::vector{1, 2, 3}), 1 + 4 + 9);
}
