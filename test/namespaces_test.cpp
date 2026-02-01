#include "../src/namespaces.h"

#include <gtest/gtest.h>

#include <string>

// Namespace alias for testing
namespace um = utils::math;

TEST(NamespacesTest, NestedNamespaceFunction) {
  constexpr int result = utils::math::add(2, 3);
  EXPECT_EQ(result, 5);
}

TEST(NamespacesTest, NestedNamespaceClass) {
  constexpr int result = utils::math::Calculator::multiply(4, 5);
  EXPECT_EQ(result, 20);
}

TEST(NamespacesTest, TopLevelNamespaceFunction) {
  const std::string result = utils::to_upper("hello");
  EXPECT_EQ(result, "HELLO");
}

TEST(NamespacesTest, NamespaceAlias) {
  constexpr int result = um::add(10, 20);  // Using alias um for utils::math
  EXPECT_EQ(result, 30);
}

TEST(NamespacesTest, UsingDeclaration) {
  // to_upper is brought into global scope via using declaration
  const std::string result = to_upper("world");
  EXPECT_EQ(result, "WORLD");
}

TEST(NamespacesTest, DifferentNamespace) {
  const std::string result = data::Processor::process("test");
  EXPECT_EQ(result, "Processed: test");
}
