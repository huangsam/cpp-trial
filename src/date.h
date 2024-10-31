#ifndef DATE_H
#define DATE_H

class Date {
 private:
  int year;
  int month;
  int day;

 public:
  Date(int year, int month, int day);

  int get_year() const { return year; }
  int get_month() const { return month; }
  int get_day() const { return day; }
};

// Primitive operators
bool operator==(const Date& lhs, const Date& rhs);
bool operator<(const Date& lhs, const Date& rhs);

// Composite operators
bool operator>(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);

#endif
