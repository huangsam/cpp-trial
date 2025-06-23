#include <iomanip>
#include <iostream>
#include <vector>

#include "date.h"
#include "factorial.h"
#include "lambda.h"
#include "person.h"

void print_date(const Date& d) {
  std::cout << d.get_year() << "/" << d.get_month() << "/" << d.get_day()
            << std::endl;
}

void print_person(const Person& p) {
  // Keep original output settings
  const std::ios_base::fmtflags originalFlags = std::cout.flags();
  const std::streamsize originalPrecision = std::cout.precision();

  std::cout << p.get_name() << " is " << p.get_age() << " years old with $";

  std::cout << std::fixed << std::setprecision(2) << std::showpoint
            << p.get_salary();

  std::cout << " as a salary" << std::endl;

  // Restore original output settings
  std::cout.flags(originalFlags);
  std::cout.precision(originalPrecision);
}

int main() {
  // date.h demo
  const auto d1 = Date(2024, 1, 1);
  print_date(d1);
  const auto d2 = Date(2024, 2, 2);
  print_date(d2);
  if (d1 < d2) {
    std::cout << "First date is older than second date" << std::endl;
  }

  // factorial.h demo
  std::cout << "factorial(4): " << factorial(4) << std::endl;

  // lambda.h demo
  std::cout << "less_than(3,4): " << less_than(3, 4) << std::endl;
  std::cout << "sum_of_squares(vector{1,2,3}): "
            << sum_of_squares(std::vector{1, 2, 3}) << std::endl;

  // person.h demo
  const auto p1 = Person("David", 21, 65000.00);
  print_person(p1);

  return 0;
}
