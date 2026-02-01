#include "../src/type_safety.h"

#include <gtest/gtest.h>

#include <map>

TEST(TypeSafetyTest, OptionalFindValue) {
  const std::map<std::string, int> data = {{"a", 1}, {"b", 2}};
  EXPECT_EQ(find_value(data, "a"), 1);
  EXPECT_EQ(find_value(data, "c"), std::nullopt);
}

TEST(TypeSafetyTest, VariantConfig) {
  ConfigValue v1 = 42;
  EXPECT_EQ(config_to_string(v1), "int: 42");

  ConfigValue v2 = std::string("hello");
  EXPECT_EQ(config_to_string(v2), "string: hello");

  ConfigValue v3 = true;
  EXPECT_EQ(config_to_string(v3), "bool: true");
}

TEST(TypeSafetyTest, AnyContainer) {
  TypeSafeContainer container;
  container.add(42);
  container.add(std::string("test"));

  EXPECT_EQ(container.size(), 2);

  const auto opt1 = container.get_as<int>(0);
  ASSERT_TRUE(opt1);
  EXPECT_EQ(*opt1, 42);

  const auto opt2 = container.get_as<std::string>(1);
  ASSERT_TRUE(opt2);
  EXPECT_EQ(*opt2, "test");

  const auto opt3 = container.get_as<double>(0);
  EXPECT_FALSE(opt3);
}

TEST(TypeSafetyTest, StringViewProcess) {
  process_string("hello world");
  SUCCEED();
}

TEST(TypeSafetyTest, StructuredBindings) {
  auto point_opt = parse_point("10,20");
  ASSERT_TRUE(point_opt);

  auto [x, y] = *point_opt;
  EXPECT_EQ(x, 10);
  EXPECT_EQ(y, 20);

  EXPECT_FALSE(parse_point("invalid"));
}

TEST(TypeSafetyTest, SafeComparisons) {
  ConfigValue a = 5;
  ConfigValue b = 5;
  EXPECT_TRUE(compare_configs(a, b));

  ConfigValue c = std::string("5");
  EXPECT_FALSE(compare_configs(a, c));
}

TEST(TypeSafetyTest, ErrorHandlingVariant) {
  const auto res1 = safe_divide(10, 2);
  ASSERT_TRUE(std::holds_alternative<std::string>(res1));
  EXPECT_EQ(std::get<std::string>(res1), "Result: 5");

  const auto res2 = safe_divide(10, 0);
  ASSERT_TRUE(std::holds_alternative<Error>(res2));
  EXPECT_EQ(std::get<Error>(res2), Error::DivisionByZero);
}

TEST(TypeSafetyTest, OptionalParse) {
  const auto res1 = safe_parse_int("123");
  ASSERT_TRUE(res1);
  EXPECT_EQ(*res1, "Parsed: 123");

  EXPECT_FALSE(safe_parse_int("abc"));
}
