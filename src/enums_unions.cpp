#include "enums_unions.h"

#include <format>
#include <string>

std::string TaggedData::to_string() const {
  switch (type) {
    using enum Type;
    case Int:
      return std::format("Int: {}", data.int_value);
    case Double:
      return std::format("Double: {}", data.double_value);
    case Char:
      return std::format("Char: {}", data.char_value);
  }
  return "Unknown";  // Should never reach here
}

std::string variant_to_string(const VariantData& var) {
  return std::visit(
      [](auto&& arg) -> std::string {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, int>) {
          return std::format("Int: {}", arg);
        } else if constexpr (std::is_same_v<T, double>) {
          return std::format("Double: {}", arg);
        } else if constexpr (std::is_same_v<T, char>) {
          return std::format("Char: {}", arg);
        }
        return "Unknown type";
      },
      var);
}
