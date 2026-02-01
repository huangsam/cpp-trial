#include "namespaces.h"

#include <algorithm>
#include <string>

namespace utils {

namespace math {

int add(int a, int b) { return a + b; }

int Calculator::multiply(int a, int b) { return a * b; }

}  // namespace math

std::string to_upper(const std::string& str) {
  std::string result = str;
  std::ranges::transform(result, result.begin(),
                         [](unsigned char c) { return std::toupper(c); });
  return result;
}

}  // namespace utils

namespace data {

std::string Processor::process(const std::string& input) {
  return "Processed: " + input;
}

}  // namespace data
