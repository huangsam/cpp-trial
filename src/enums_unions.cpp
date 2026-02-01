#include "enums_unions.h"

#include <sstream>
#include <string>

std::string TaggedData::to_string() const {
  std::ostringstream oss;
  switch (type) {
    case Type::Int:
      oss << "Int: " << data.int_value;
      break;
    case Type::Double:
      oss << "Double: " << data.double_value;
      break;
    case Type::Char:
      oss << "Char: " << data.char_value;
      break;
  }
  return oss.str();
}

std::string variant_to_string(const VariantData& var) {
  return std::visit([](auto&& arg) -> std::string {
    using T = std::decay_t<decltype(arg)>;
    std::ostringstream oss;
    if constexpr (std::is_same_v<T, int>) {
      oss << "Int: " << arg;
    } else if constexpr (std::is_same_v<T, double>) {
      oss << "Double: " << arg;
    } else if constexpr (std::is_same_v<T, char>) {
      oss << "Char: " << arg;
    }
    return oss.str();
  }, var);
}