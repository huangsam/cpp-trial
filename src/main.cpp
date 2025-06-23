#include <format>
#include <iostream>
#include <vector>

#include "date.h"
#include "factorial.h"
#include "lambda.h"
#include "person.h"

// Specialization for Date
template <>
struct std::formatter<Date> : std::formatter<std::string> {
  static auto format(const Date& d, std::format_context& ctx) {
    return std::format_to(ctx.out(), "{}/{}/{}", d.get_year(), d.get_month(),
                          d.get_day());
  }
};

// Specialization for Person
template <>
struct std::formatter<Person> : std::formatter<std::string> {
  static auto format(const Person& p, std::format_context& ctx) {
    // Using a format specifier for floating-point numbers (:.2f)
    return std::format_to(ctx.out(),
                          "{} is {} years old with ${:.2f} as a salary",
                          p.get_name(), p.get_age(), p.get_salary());
  }
};

int main() {
  // date.h demo
  const auto d1 = Date(2024, 1, 1);
  std::cout << std::format("{}\n", d1);
  const auto d2 = Date(2024, 2, 2);
  std::cout << std::format("{}\n", d2);
  if (d1 < d2) {
    std::cout << std::format("First date is older than second date\n");
  }

  // factorial.h demo
  std::cout << std::format("factorial(4): {}\n", factorial(4));

  // lambda.h demo
  std::cout << std::format("less_than(3,4): {}\n", less_than(3, 4));
  std::cout << std::format("sum_of_squares(vector{{1,2,3}}): {}\n",
                           sum_of_squares(std::vector{1, 2, 3}));

  // person.h demo
  const auto p1 = Person("David", 21, 65000.00);
  std::cout << std::format("{}\n", p1);

  return 0;
}
