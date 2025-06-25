#include <format>
#include <iostream>
#include <vector>

#include "date.h"
#include "factorial.h"
#include "lambda.h"
#include "person.h"

int main() {
  // date.h demo
  const auto date1 = Date(Year(2024), Month(1), Day(1));
  std::cout << std::format("{}\n", date1);
  const auto date2 = Date(Year(2024), Month(2), Day(2));
  std::cout << std::format("{}\n", date2);
  if (date1 < date2) {
    std::cout << std::format("First date is older than second date\n");
  }

  // factorial.h demo
  std::cout << std::format("factorial(4): {}\n", factorial(4));

  // lambda.h demo
  std::cout << std::format("less_than(3,4): {}\n",
                           less_than(ValueOne(3), ValueTwo(4)));
  std::cout << std::format("sum_of_squares(vector{{1,2,3}}): {}\n",
                           sum_of_squares(std::vector{1, 2, 3}));

  // person.h demo
  const auto person = Person("David", Age(21), Salary(65000.00));
  std::cout << std::format("{}\n", person);

  return 0;
}
