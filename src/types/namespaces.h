#ifndef NAMESPACES_H
#define NAMESPACES_H

#include <string>

// Top-level namespace
namespace utils {

// Nested namespace
namespace math {

// add performs integer addition in the math nested namespace.
constexpr int add(int a, int b) { return a + b; }

// Calculator provides math operations in the math nested namespace.
class Calculator {
 public:
  static constexpr int multiply(int a, int b) { return a * b; }
};

}  // namespace math

// to_upper converts a string to uppercase in the utils namespace.
std::string to_upper(std::string_view str);

}  // namespace utils

// Using declaration (brings specific name into scope)
using utils::to_upper;

// Another namespace for demonstration
namespace data {

// Processor handles data operations in the data namespace.
class Processor {
 public:
  static std::string process(std::string_view input);
};

}  // namespace data

#endif  // NAMESPACES_H
