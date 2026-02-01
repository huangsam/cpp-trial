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
      []<typename T>(T&& arg) -> std::string {
        using DecayedT = std::decay_t<T>;
        if constexpr (std::is_same_v<DecayedT, int>) {
          return std::format("Int: {}", arg);
        } else if constexpr (std::is_same_v<DecayedT, double>) {
          return std::format("Double: {}", arg);
        } else if constexpr (std::is_same_v<DecayedT, char>) {
          return std::format("Char: {}", arg);
        }
        return "Unknown type";
      },
      var);
}
