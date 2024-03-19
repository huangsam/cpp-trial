#include "../src/lambda.h"

#include <gtest/gtest.h>

TEST(LambdaTest, LessThanComparison) { EXPECT_EQ(lessThan(3, 4), true); }
