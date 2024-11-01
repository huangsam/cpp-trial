#include <iostream>
#include <vector>

#include "date.h"
#include "factorial.h"
#include "lambda.h"
#include "person.h"

void print_date(Date d) {
  std::cout << d.get_year() << "/" << d.get_month() << "/" << d.get_day() << "\n";
}

void print_person(Person p) {
  std::cout << p.get_name() << " is " << p.get_age() << " years old\n";
}

int main() {
  // date.h demo
  auto d1 = Date(2024, 1, 1);
  print_date(d1);
  auto d2 = Date(2024, 2, 2);
  print_date(d2);
  if (d1 < d2) {
    std::cout << "First date is older than second date\n";
  }

  // factorial.h demo
  std::cout << "factorial(4): " << factorial(4) << std::endl;

  // lambda.h demo
  std::cout << "less_than(3,4): " << less_than(3, 4) << std::endl;
  std::cout << "sum_of_squares(vector{1,2,3}): "
       << sum_of_squares(std::vector{1, 2, 3}) << std::endl;

  // person.h demo
  auto p1 = Person("David", 21);
  print_person(p1);

  return 0;
}
