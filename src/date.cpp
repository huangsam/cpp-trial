#include "date.h"

#include <iostream>

Date::Date(int year, int month, int day) : year(year), month(month), day(day) {}

bool operator==(const Date& lhs, const Date& rhs) {
  return lhs.getYear() == rhs.getYear() && lhs.getMonth() == rhs.getMonth() &&
         lhs.getDay() == rhs.getDay();
}

bool operator<(const Date& lhs, const Date& rhs) {
  int year_delta = lhs.getYear() - rhs.getYear();
  int month_delta = lhs.getMonth() - rhs.getMonth();
  int day_delta = lhs.getDay() - rhs.getDay();
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
