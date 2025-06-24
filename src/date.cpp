#include "date.h"

Date::Date(const Year year, const Month month, const Day day)
    : year(year.value), month(month.value), day(day.value) {}

bool operator==(const Date& lhs, const Date& rhs) {
  return lhs.get_year() == rhs.get_year() &&
         lhs.get_month() == rhs.get_month() && lhs.get_day() == rhs.get_day();
}

bool operator<(const Date& lhs, const Date& rhs) {
  const int year_delta = lhs.get_year() - rhs.get_year();
  const int month_delta = lhs.get_month() - rhs.get_month();
  const int day_delta = lhs.get_day() - rhs.get_day();
  if (year_delta) return year_delta < 0;
  if (month_delta) return month_delta < 0;
  return day_delta < 0;
}

bool operator>(const Date& lhs, const Date& rhs) {
  return !(lhs < rhs || lhs == rhs);
}

bool operator<=(const Date& lhs, const Date& rhs) {
  return lhs < rhs || lhs == rhs;
}

bool operator>=(const Date& lhs, const Date& rhs) { return !(lhs < rhs); }

bool operator!=(const Date& lhs, const Date& rhs) { return !(lhs == rhs); }
