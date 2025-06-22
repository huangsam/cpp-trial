#ifndef DATE_HPP
#define DATE_HPP

class Date {
 private:
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
bool operator==(const Date &lhs, const Date &rhs);
bool operator<(const Date &lhs, const Date &rhs);

// Composite operators
bool operator>(const Date &lhs, const Date &rhs);
bool operator<=(const Date &lhs, const Date &rhs);
bool operator>=(const Date &lhs, const Date &rhs);
bool operator!=(const Date &lhs, const Date &rhs);

#endif
