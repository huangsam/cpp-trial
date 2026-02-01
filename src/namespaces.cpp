#include "namespaces.h"

#include <algorithm>
#include <cctype>
#include <string>

namespace utils {

namespace math {

int add(int a, int b) { return a + b; }

int Calculator::multiply(int a, int b) const { return a * b; }

}  // namespace math

std::string to_upper(const std::string& str) {
  std::string result = str;
  std::transform(result.begin(), result.end(), result.begin(),
                 [](unsigned char c) { return std::toupper(c); });
  return result;
}

}  // namespace utils

namespace data {

std::string Processor::process(const std::string& input) const {
  return "Processed: " + input;
}

}  // namespace data
