#ifndef NAMESPACES_H
#define NAMESPACES_H

#include <string>

// Top-level namespace
namespace utils {

// Nested namespace
namespace math {

// Function in nested namespace
constexpr int add(int a, int b) { return a + b; }

// Class in nested namespace
class Calculator {
 public:
  static constexpr int multiply(int a, int b) { return a * b; }
};

}  // namespace math

// Function in top-level namespace
std::string to_upper(const std::string& str);

}  // namespace utils

// Using declaration (brings specific name into scope)
using utils::to_upper;

// Another namespace for demonstration
namespace data {

class Processor {
 public:
  static std::string process(const std::string& input);
};

}  // namespace data

#endif  // NAMESPACES_H
