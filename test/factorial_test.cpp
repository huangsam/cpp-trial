#include "../src/factorial.h"

#include <gtest/gtest.h>

#include <stdexcept>

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
  EXPECT_THROW(factorial(-1), std::invalid_argument);
  EXPECT_THROW(factorial(-99), std::invalid_argument);
}

TEST(FactorialTest, TemplateSpecialization) {
  // Test template with different integral types
  EXPECT_EQ(factorial<int8_t>(3), 6);
  EXPECT_EQ(factorial<int16_t>(4), 24);
  EXPECT_EQ(factorial<int32_t>(5), 120);
  EXPECT_EQ(factorial<int64_t>(6), 720);
}

TEST(FactorialTest, TemplateConstraints) {
  // This should fail to compile due to concept constraints
  // factorial<double>(3);  // Would not compile - double is not integral
  // factorial<std::string>(3);  // Would not compile - string is not integral
}
