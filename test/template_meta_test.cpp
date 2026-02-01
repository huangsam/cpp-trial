#include "../src/template_meta.h"

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

// Test SFINAE with enable_if
TEST(TemplateMetaTest, SFINAE_EnableIf) {
  testing::internal::CaptureStdout();
  print_if_integral(42);
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_NE(output.find("42 is an integral type"), std::string::npos);

  testing::internal::CaptureStdout();
  print_if_floating(3.14);
  output = testing::internal::GetCapturedStdout();
  EXPECT_NE(output.find("3.14 is a floating-point type"), std::string::npos);
}

// Test type traits
TEST(TemplateMetaTest, TypeTraits) {
  EXPECT_TRUE(IsContainer<std::vector<int>>::value);
  EXPECT_FALSE(IsContainer<int>::value);

  testing::internal::CaptureStdout();
  const std::vector<int> vec = {1, 2, 3};
  print_container_size(vec);
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_NE(output.find("Container size: 3"), std::string::npos);
}

// Test constexpr programming
TEST(TemplateMetaTest, ConstexprProgramming) {
  static_assert(factorial(0) == 1, "0! should be 1");
  static_assert(factorial(1) == 1, "1! should be 1");
  static_assert(factorial(5) == 120, "5! should be 120");

  static_assert(Power<2, 0>::value == 1, "2^0 should be 1");
  static_assert(Power<2, 3>::value == 8, "2^3 should be 8");
  static_assert(Power<3, 2>::value == 9, "3^2 should be 9");

  EXPECT_EQ(factorial(5), 120);
  EXPECT_EQ((Power<2, 3>::value), 8);
}

// Test variadic templates
TEST(TemplateMetaTest, VariadicTemplates) {
  EXPECT_EQ(sum_all(1, 2, 3, 4), 10);
  EXPECT_EQ(sum_all(1.5, 2.5), 4.0);

  testing::internal::CaptureStdout();
  print_all("a", "b", "c");
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_NE(output.find("abc"), std::string::npos);
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

// Test CRTP
TEST(TemplateMetaTest, CRTP) {
  const MyClass obj;
  testing::internal::CaptureStdout();
  obj.print();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_NE(output.find("Printing MyClass"), std::string::npos);
}

// Test tag dispatch
TEST(TemplateMetaTest, TagDispatch) {
  testing::internal::CaptureStdout();
  dispatch_process(42);
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_NE(output.find("42 is processed as integral"), std::string::npos);

  testing::internal::CaptureStdout();
  dispatch_process(3.14);
  output = testing::internal::GetCapturedStdout();
  EXPECT_NE(output.find("3.14 is processed as floating-point"),
            std::string::npos);

  testing::internal::CaptureStdout();
  dispatch_process("hello");
  output = testing::internal::GetCapturedStdout();
  EXPECT_NE(output.find("hello is processed as other type"), std::string::npos);
}

// Test overall demonstration function
TEST(TemplateMetaTest, DemonstrateFunction) {
  testing::internal::CaptureStdout();
  demonstrate_template_meta();
  const std::string output = testing::internal::GetCapturedStdout();
  EXPECT_FALSE(output.empty());
}
