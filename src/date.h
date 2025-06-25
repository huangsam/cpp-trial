#ifndef DATE_H
#define DATE_H

#include <format>
#include <stdexcept>

struct Year {
  explicit Year(const int year) : value(year) {
    if (value <= 0) {
      throw std::out_of_range("Year must be positive.");
    }
  }
  int value;
};

struct Month {
  static constexpr int MIN_MONTH = 1;
  static constexpr int MAX_MONTH = 12;
  explicit Month(const int month) : value(month) {
    if (value < MIN_MONTH || value > MAX_MONTH) {
      throw std::out_of_range("Month must be between 1 and 12.");
    }
  }
  int value;
};

struct Day {
  static constexpr int MIN_DAY = 1;
  static constexpr int MAX_DAY = 31;
  explicit Day(const int day) : value(day) {
    if (value < MIN_DAY || value > MAX_DAY) {
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
  static auto format(const Date& date, std::format_context& ctx) {
    return std::format_to(ctx.out(), "{}/{}/{}", date.get_year(), date.get_month(),
                          date.get_day());
  }
};

#endif  // DATE_H
