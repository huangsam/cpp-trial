#ifndef TYPE_SAFETY_H
#define TYPE_SAFETY_H

#include <any>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

// find_value safely retrieves an integer from a map, returning optional if not
// found.
std::optional<int> find_value(const std::map<std::string, int>& data,
                              std::string_view key);

// ConfigValue is a type-safe union holding int, string, or bool.
using ConfigValue = std::variant<int, std::string, bool>;

// config_to_string converts any ConfigValue variant to a string representation.
std::string config_to_string(const ConfigValue& val);

// TypeSafeContainer demonstrates type-erased storage using std::any.
class TypeSafeContainer {
 public:
  void add(std::any value);
  [[nodiscard]] std::any get(size_t index) const;
  [[nodiscard]] size_t size() const;

  // Safe retrieval with type checking (demonstrates error handling)
  template <typename T>
  std::optional<T> get_as(size_t index) const {
    if (index >= data_.size()) return std::nullopt;
    try {
      return std::any_cast<T>(data_[index]);
    } catch (const std::bad_any_cast&) {
      return std::nullopt;
    }
  }

 private:
  std::vector<std::any> data_;
};

// process_string demonstrates std::string_view for efficient string processing.
void process_string(std::string_view sv);

// Point represents a 2D coordinate with structured binding support.
struct Point {
  int x, y;
};

// parse_point parses a comma-separated coordinate string into a Point.
std::optional<Point> parse_point(std::string_view input);

// compare_configs safely compares two ConfigValue variants for equality.
bool compare_configs(const ConfigValue& a, const ConfigValue& b);

// Error represents different error conditions for Result type.
enum class Error { InvalidInput, DivisionByZero, NotFound };

// Result is a variant that holds either a success string or an error.
using Result = std::variant<std::string, Error>;

// safe_divide performs division with error handling via Result variant.
Result safe_divide(int a, int b);

// safe_parse_int parses a string to integer, returning optional.
std::optional<std::string> safe_parse_int(std::string_view str);

#endif  // TYPE_SAFETY_H
