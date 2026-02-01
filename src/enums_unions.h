#ifndef ENUMS_UNIONS_H
#define ENUMS_UNIONS_H

#include <string>
#include <variant>

// Unscoped enum (traditional)
enum Color { Red, Green, Blue };

// Scoped enum (enum class)
enum class Status { Idle, Running, Stopped };

// Union for memory-efficient storage of different types
union Data {
  int int_value;
  double double_value;
  char char_value;
};

// Struct demonstrating union usage with a tag
struct TaggedData {
  enum class Type { Int, Double, Char } type;
  Data data;

  TaggedData(int val) : type(Type::Int) { data.int_value = val; }
  TaggedData(double val) : type(Type::Double) { data.double_value = val; }
  TaggedData(char val) : type(Type::Char) { data.char_value = val; }

  std::string to_string() const;
};

// Modern alternative: std::variant
using VariantData = std::variant<int, double, char>;

std::string variant_to_string(const VariantData& var);

#endif  // ENUMS_UNIONS_H