#include "advanced/template_meta.h"

#include <gtest/gtest.h>

#include <string>
#include <vector>

// Test template specialization
TEST(TemplateMetaTest, IsPointerSpecialization) {
  EXPECT_FALSE(IsPointer<int>::value);
  EXPECT_TRUE(IsPointer<int*>::value);
  EXPECT_TRUE(IsPointer<const int*>::value);
  EXPECT_FALSE(IsPointer<std::string>::value);
}

// Test type traits
TEST(TemplateMetaTest, TypeTraits) {
  EXPECT_TRUE(IsContainer<std::vector<int>>::value);
  EXPECT_FALSE(IsContainer<int>::value);
}

// Test constexpr programming
TEST(TemplateMetaTest, ConstexprProgramming) {
  static_assert(Minimal::factorial(0) == 1, "0! should be 1");
  static_assert(Minimal::factorial(1) == 1, "1! should be 1");
  static_assert(Minimal::factorial(5) == 120, "5! should be 120");

  static_assert(Power<2, 0>::value == 1, "2^0 should be 1");
  static_assert(Power<2, 3>::value == 8, "2^3 should be 8");
  static_assert(Power<3, 2>::value == 9, "3^2 should be 9");

  EXPECT_EQ(Minimal::factorial(5), 120);
  EXPECT_EQ((Power<2, 3>::value), 8);
}

// Test variadic templates
TEST(TemplateMetaTest, VariadicTemplates) {
  EXPECT_EQ(sum_all(1, 2, 3, 4), 10);
  EXPECT_EQ(sum_all(1.5, 2.5), 4.0);
}

// Test template recursion
TEST(TemplateMetaTest, TemplateRecursion) {
  static_assert(Fibonacci<0>::value == 0, "Fib(0) should be 0");
  static_assert(Fibonacci<1>::value == 1, "Fib(1) should be 1");
  static_assert(Fibonacci<2>::value == 1, "Fib(2) should be 1");
  static_assert(Fibonacci<5>::value == 5, "Fib(5) should be 5");
  static_assert(Fibonacci<10>::value == 55, "Fib(10) should be 55");

  EXPECT_EQ(Fibonacci<10>::value, 55);
}
