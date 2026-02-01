#ifndef DATE_H
#define DATE_H

#include <format>
#include <stdexcept>

struct Year {
  static constexpr int MIN_YEAR = 1;
  explicit Year(const int year) : value(year) {
    if (value < MIN_YEAR) {
      throw std::out_of_range(std::format("Year must be at least {}, got: {}", MIN_YEAR, year));
    }
  }
  int value;
};

struct Month {
  static constexpr int MIN_MONTH = 1;
  static constexpr int MAX_MONTH = 12;
  explicit Month(const int month) : value(month) {
    if (value < MIN_MONTH || value > MAX_MONTH) {
      throw std::out_of_range(std::format("Month must be between {} and {}, got: {}", MIN_MONTH, MAX_MONTH, month));
    }
  }
  int value;
};

struct Day {
  static constexpr int MIN_DAY = 1;
  static constexpr int MAX_DAY = 31;
  explicit Day(const int day) : value(day) {
    if (value < MIN_DAY || value > MAX_DAY) {
      throw std::out_of_range(std::format("Day must be between {} and {} (note: month-specific validation not performed), got: {}", MIN_DAY, MAX_DAY, day));
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

  [[nodiscard]] constexpr int get_year() const { return year; }
  [[nodiscard]] constexpr int get_month() const { return month; }
  [[nodiscard]] constexpr int get_day() const { return day; }

  // Three-way comparison operator
  friend constexpr auto operator<=>(const Date& lhs, const Date& rhs) {
    if (auto cmp = lhs.get_year() <=> rhs.get_year(); cmp != 0) return cmp;
    if (auto cmp = lhs.get_month() <=> rhs.get_month(); cmp != 0) return cmp;
    return lhs.get_day() <=> rhs.get_day();
  }

  // Equality operator (explicit for clarity)
  friend constexpr bool operator==(const Date& lhs, const Date& rhs) = default;
};

// Specialization for Date
template <>
struct std::formatter<Date> : std::formatter<std::string> {
  static auto format(const Date& date, std::format_context& ctx) {
    return std::format_to(ctx.out(), "{}/{}/{}", date.get_year(),
                          date.get_month(), date.get_day());
  }
};

#endif  // DATE_H
