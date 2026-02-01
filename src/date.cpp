#include "date.h"

Date::Date(const Year year, const Month month, const Day day)
    : year(year.value), month(month.value), day(day.value) {}
