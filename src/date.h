#ifndef DATE_H
#define DATE_H

class Date {
 private:
  int year;
  int month;
  int day;

 public:
  Date(int year, int month, int day);

  int getYear() const { return year; }
  int getMonth() const { return month; }
  int getDay() const { return day; }
};

// Primitive operators
bool operator==(Date const& lhs, Date const& rhs);
bool operator<(Date const& lhs, Date const& rhs);

// Composite operators
bool operator>(Date const& lhs, Date const& rhs);
bool operator<=(Date const& lhs, Date const& rhs);
bool operator>=(Date const& lhs, Date const& rhs);

#endif
