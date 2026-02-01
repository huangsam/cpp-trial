#include "type_safety.h"

#include <charconv>
#include <format>

std::optional<int> find_value(const std::map<std::string, int>& data,
                              const std::string_view key) {
  if (const auto it = data.find(std::string(key)); it != data.end()) {
    return it->second;
  }
  return std::nullopt;
}

std::string config_to_string(const ConfigValue& val) {
  return std::visit(
      []<typename VS>(const VS& v) -> std::string {
        using T = std::decay_t<VS>;
        if constexpr (std::is_same_v<T, int>) {
          return std::format("int: {}", v);
        } else if constexpr (std::is_same_v<T, std::string>) {
          return std::format("string: {}", v);
        } else if constexpr (std::is_same_v<T, bool>) {
          return std::format("bool: {}", v ? "true" : "false");
        }
        return "unknown";
      },
      val);
}

void TypeSafeContainer::add(std::any value) {
  data_.push_back(std::move(value));
}

std::any TypeSafeContainer::get(const size_t index) const {
  if (index < data_.size()) {
    return data_[index];
  }
  throw std::out_of_range("Index out of range");
}

size_t TypeSafeContainer::size() const { return data_.size(); }

void process_string(const std::string_view sv) {
  // std::string_view avoids copying; efficient for read-only operations
  int vowels = 0;
  for (const char c : sv) {
    if (std::string_view("aeiouAEIOU").find(c) != std::string_view::npos) {
      ++vowels;
    }
  }
  // Use the vowels count to avoid unused variable warning
  (void)vowels;
}

std::optional<Point> parse_point(std::string_view input) {
  const size_t comma = input.find(',');
  if (comma == std::string_view::npos) return std::nullopt;

  int x, y;
  if (auto [ptr, ec] = std::from_chars(input.data(), input.data() + comma, x);
      ec != std::errc{})
    return std::nullopt;

  auto [ptr, ec] =
      std::from_chars(input.data() + comma + 1, input.data() + input.size(), y);
  if (ec != std::errc{}) return std::nullopt;

  return Point{x, y};
}

bool compare_configs(const ConfigValue& a, const ConfigValue& b) {
  return std::visit(
      []<typename LH, typename RH>(const LH& lhs, const RH& rhs) -> bool {
        using L = std::decay_t<LH>;
        using R = std::decay_t<RH>;
        if constexpr (std::is_same_v<L, R>) {
          return lhs == rhs;
        } else {
          return false;
        }
      },
      a, b);
}

Result safe_divide(const int a, const int b) {
  if (b == 0) {
    return Error::DivisionByZero;
  }
  return std::format("Result: {}", a / b);
}

std::optional<std::string> safe_parse_int(const std::string_view str) {
  int value;
  if (auto [ptr, ec] =
          std::from_chars(str.data(), str.data() + str.size(), value);
      ec == std::errc{}) {
    return std::format("Parsed: {}", value);
  }
  return std::nullopt;
}
