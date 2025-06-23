#ifndef DATE_HPP
#define DATE_HPP

#include <format>

class Date {
  int year;
  int month;
  int day;

 public:
  Date(int year, int month, int day);

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
};

#endif
