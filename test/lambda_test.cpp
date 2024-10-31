#include "../src/lambda.h"

#include <gtest/gtest.h>

#include <vector>

TEST(LambdaTest, less_thanComparison) {
  EXPECT_EQ(less_than(3, 3), false);
  EXPECT_EQ(less_than(3, 4), true);
  EXPECT_EQ(less_than(-4, -3), true);
}

TEST(LambdaTest, sum_of_squares) {
  EXPECT_EQ(sum_of_squares(std::vector{1, 1, 1}), 3);
  EXPECT_EQ(sum_of_squares(std::vector{1, 2, 3}), 1 + 4 + 9);
}
