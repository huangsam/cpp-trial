#include "date.hpp"

Date::Date(int year, int month, int day) : year(year), month(month), day(day) {}

bool operator==(const Date &lhs, const Date &rhs) {
  return lhs.get_year() == rhs.get_year() &&
         lhs.get_month() == rhs.get_month() && lhs.get_day() == rhs.get_day();
}

bool operator<(const Date &lhs, const Date &rhs) {
  int year_delta = lhs.get_year() - rhs.get_year();
  int month_delta = lhs.get_month() - rhs.get_month();
  int day_delta = lhs.get_day() - rhs.get_day();
  if (year_delta) return year_delta < 0;
  if (month_delta) return month_delta < 0;
  return day_delta < 0;
}

bool operator>(const Date &lhs, const Date &rhs) {
  return !(lhs < rhs || lhs == rhs);
}

bool operator<=(const Date &lhs, const Date &rhs) {
  return lhs < rhs || lhs == rhs;
}

bool operator>=(const Date &lhs, const Date &rhs) { return !(lhs < rhs); }

bool operator!=(const Date &lhs, const Date &rhs) { return !(lhs == rhs); }
