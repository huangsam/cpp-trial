#include "../src/namespaces.h"

#include <gtest/gtest.h>

#include <string>

// Namespace alias for testing
namespace um = utils::math;

TEST(NamespacesTest, NestedNamespaceFunction) {
  int result = utils::math::add(2, 3);
  EXPECT_EQ(result, 5);
}

TEST(NamespacesTest, NestedNamespaceClass) {
  utils::math::Calculator calc;
  int result = calc.multiply(4, 5);
  EXPECT_EQ(result, 20);
}

TEST(NamespacesTest, TopLevelNamespaceFunction) {
  std::string result = utils::to_upper("hello");
  EXPECT_EQ(result, "HELLO");
}

TEST(NamespacesTest, NamespaceAlias) {
  int result = um::add(10, 20);  // Using alias um for utils::math
  EXPECT_EQ(result, 30);
}

TEST(NamespacesTest, UsingDeclaration) {
  // to_upper is brought into global scope via using declaration
  std::string result = to_upper("world");
  EXPECT_EQ(result, "WORLD");
}

TEST(NamespacesTest, DifferentNamespace) {
  data::Processor proc;
  std::string result = proc.process("test");
  EXPECT_EQ(result, "Processed: test");
}
