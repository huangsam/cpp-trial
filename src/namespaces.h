#ifndef NAMESPACES_H
#define NAMESPACES_H

#include <string>

// Top-level namespace
namespace utils {

// Nested namespace
namespace math {

// Function in nested namespace
int add(int a, int b);

// Class in nested namespace
class Calculator {
 public:
  int multiply(int a, int b) const;
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
  std::string process(const std::string& input) const;
};

}  // namespace data

#endif  // NAMESPACES_H
