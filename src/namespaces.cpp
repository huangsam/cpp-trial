#include "namespaces.h"

#include <algorithm>
#include <string>

namespace utils {

namespace math {}  // namespace math

std::string to_upper(const std::string_view str) {
  std::string result(str);
  std::ranges::transform(result, result.begin(),
                         [](const unsigned char c) { return std::toupper(c); });
  return result;
}

}  // namespace utils

namespace data {

std::string Processor::process(const std::string_view input) {
  return "Processed: " + std::string(input);
}

}  // namespace data
