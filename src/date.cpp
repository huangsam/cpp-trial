#include "date.h"

#include <iostream>

Date::Date(int year, int month, int day) : year(year), month(month), day(day) {}

bool operator<(Date const & lhs, Date const & rhs) {
  return lhs.getYear() < rhs.getYear() || lhs.getMonth() < rhs.getMonth() || lhs.getDay() < rhs.getDay();
}
