#ifndef DATE_H
#define DATE_H

#include <format>
#include <stdexcept>

struct Year {
  explicit Year(const int y) : value(y) {
    if (value <= 0) {
      throw std::out_of_range("Year must be positive.");
    }
  }
  int value;
};

struct Month {
  explicit Month(const int m) : value(m) {
    if (value < 1 || value > 12) {
      throw std::out_of_range("Month must be between 1 and 12.");
    }
  }
  int value;
};

struct Day {
  explicit Day(const int d) : value(d) {
    if (value < 1 || value > 31) {
      throw std::out_of_range("Day must be between 1 and 31.");
    }
  }
  int value;
};

class Date {
  int year;
  int month;
  int day;

 public:
  Date(Year year, Month month, Day day);

  [[nodiscard]] int get_year() const { return year; }
  [[nodiscard]] int get_month() const { return month; }
  [[nodiscard]] int get_day() const { return day; }
};

// Primitive operators
bool operator==(const Date& lhs, const Date& rhs);
bool operator<(const Date& lhs, const Date& rhs);

// Composite operators
bool operator>(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);

// Specialization for Date
template <>
struct std::formatter<Date> : std::formatter<std::string> {
  static auto format(const Date& d, std::format_context& ctx) {
    return std::format_to(ctx.out(), "{}/{}/{}", d.get_year(), d.get_month(),
                          d.get_day());
  }

  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin();
    auto end = ctx.end();
    while (it != end && *it != '}') {
      ++it;
    }
    return it;
  }
};

#endif  // DATE_H
