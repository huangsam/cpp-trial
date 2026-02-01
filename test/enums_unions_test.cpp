#include "../src/enums_unions.h"

#include <gtest/gtest.h>

#include <string>

TEST(EnumsUnionsTest, UnscopedEnum) {
  Color c = Red;
  EXPECT_EQ(c, 0);  // Unscoped enums are implicitly convertible to int
  c = Green;
  EXPECT_EQ(c, 1);
}

TEST(EnumsUnionsTest, ScopedEnum) {
  Status s = Status::Idle;
  EXPECT_EQ(static_cast<int>(s), 0);  // Scoped enums require explicit cast
  s = Status::Running;
  EXPECT_EQ(static_cast<int>(s), 1);
}

TEST(EnumsUnionsTest, TaggedUnion) {
  TaggedData int_data(42);
  EXPECT_EQ(int_data.type, TaggedData::Type::Int);
  EXPECT_EQ(int_data.to_string(), "Int: 42");

  TaggedData double_data(3.14);
  EXPECT_EQ(double_data.type, TaggedData::Type::Double);
  EXPECT_EQ(double_data.to_string(), "Double: 3.14");

  TaggedData char_data('A');
  EXPECT_EQ(char_data.type, TaggedData::Type::Char);
  EXPECT_EQ(char_data.to_string(), "Char: A");
}

TEST(EnumsUnionsTest, Variant) {
  VariantData int_var = 42;
  EXPECT_EQ(variant_to_string(int_var), "Int: 42");

  VariantData double_var = 3.14;
  EXPECT_EQ(variant_to_string(double_var), "Double: 3.14");

  VariantData char_var = 'A';
  EXPECT_EQ(variant_to_string(char_var), "Char: A");
}

TEST(EnumsUnionsTest, UnionMemorySharing) {
  Data d;
  d.int_value = 100;
  EXPECT_EQ(d.int_value, 100);

  // Overwrite with double (shares memory)
  d.double_value = 2.5;
  EXPECT_DOUBLE_EQ(d.double_value, 2.5);

  // Note: int_value is now undefined, demonstrating memory sharing
}