#ifndef ENUMS_UNIONS_H
#define ENUMS_UNIONS_H

#include <string>
#include <variant>

// Color is an unscoped enum demonstrating traditional enumeration.
enum Color { Red, Green, Blue };

// Status is a scoped enum (enum class) demonstrating type-safe enumeration.
enum class Status { Idle, Running, Stopped };

// Data is a union that stores one of several types (int, double, char) in
// shared memory.
union Data {
  int int_value;
  double double_value;
  char char_value;
};

// TaggedData wraps a union with a type tag to safely track which member is
// active.
struct TaggedData {
  enum class Type { Int, Double, Char } type;
  Data data{};

  TaggedData(int val) : type(Type::Int) { data.int_value = val; }
  TaggedData(double val) : type(Type::Double) { data.double_value = val; }
  TaggedData(char val) : type(Type::Char) { data.char_value = val; }

  [[nodiscard]] std::string to_string() const;
};

// VariantData is a type-safe union using std::variant (modern alternative to
// tagged unions).
using VariantData = std::variant<int, double, char>;

// variant_to_string converts a VariantData to a readable string representation.
std::string variant_to_string(const VariantData& var);

#endif  // ENUMS_UNIONS_H
