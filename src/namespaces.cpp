#include "namespaces.h"

#include <algorithm>
#include <string>

namespace utils {

namespace math {}  // namespace math

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
