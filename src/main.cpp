#include <iostream>
#include <vector>

#include "date.hpp"
#include "factorial.hpp"
#include "lambda.hpp"
#include "person.hpp"

void print_date(Date d) {
  std::cout << d.get_year() << "/" << d.get_month() << "/" << d.get_day() << "\n";
}

void print_person(Person p) {
  std::cout << p.get_name() << " is " << p.get_age() << " years old\n";
}

int main() {
  // date.hpp demo
  auto d1 = Date(2024, 1, 1);
  print_date(d1);
  auto d2 = Date(2024, 2, 2);
  print_date(d2);
  if (d1 < d2) {
    std::cout << "First date is older than second date\n";
  }

  // factorial.hpp demo
  std::cout << "factorial(4): " << factorial(4) << std::endl;

  // lambda.hpp demo
  std::cout << "less_than(3,4): " << less_than(3, 4) << std::endl;
  std::cout << "sum_of_squares(vector{1,2,3}): "
       << sum_of_squares(std::vector{1, 2, 3}) << std::endl;

  // person.hpp demo
  auto p1 = Person("David", 21);
  print_person(p1);

  return 0;
}
