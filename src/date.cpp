#include "date.h"

#include <iostream>

Date::Date(int year, int month, int day) : year(year), month(month), day(day) {}

bool operator<(Date const & lhs, Date const & rhs) {
  if (lhs.getYear() < rhs.getYear()) {
    return true;
  } else if (lhs.getMonth() < rhs.getMonth()) {
    return true;
  } else {
    return lhs.getDay() < rhs.getDay();
  }
}
