#ifndef TYPE_SAFETY_H
#define TYPE_SAFETY_H

#include <any>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

// 1. std::optional for optional values (replacing pointers for "not found")
std::optional<int> find_value(const std::map<std::string, int>& data,
                              std::string_view key);

// 2. std::variant for type-safe unions (improving on raw unions)
using ConfigValue = std::variant<int, std::string, bool>;
std::string config_to_string(const ConfigValue& val);

// 3. std::any for type-erased storage
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

// 4. std::string_view for non-owning string references
void process_string(std::string_view sv);

// Structured bindings example
struct Point {
  int x, y;
};
std::optional<Point> parse_point(std::string_view input);

// Safe comparisons and operations
bool compare_configs(const ConfigValue& a, const ConfigValue& b);

// Error handling patterns
enum class Error { InvalidInput, DivisionByZero, NotFound };
using Result = std::variant<std::string, Error>;
Result safe_divide(int a, int b);

// Another error handling example with optional
std::optional<std::string> safe_parse_int(std::string_view str);

#endif  // TYPE_SAFETY_H
