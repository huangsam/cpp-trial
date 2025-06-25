#ifndef PERSON_H
#define PERSON_H

#include <format>
#include <stdexcept>
#include <string>
#include <vector>

struct Age {
  explicit Age(const int age) : value(age) {
    if (value < 1) {
      throw std::invalid_argument("Age must be positive");
    }
  }
  int value;
};

struct Salary {
  explicit Salary(const double salary) : value(salary) {
    if (value < 0.0) {
      throw std::invalid_argument(std::format("Salary must be non-negative"));
    }
  }
  double value;
};

class Person {
  std::string name;
  int age;
  double salary;

 public:
  Person(std::string name, Age age, Salary salary);

  [[nodiscard]] std::string get_name() const { return name; }
  [[nodiscard]] int get_age() const { return age; }
  [[nodiscard]] double get_salary() const { return salary; }
};

// Specialization for Person
template <>
struct std::formatter<Person> : std::formatter<std::string> {
  static auto format(const Person& person, std::format_context& ctx) {
    // Using a format specifier for floating-point numbers (:.2f)
    return std::format_to(ctx.out(),
                          "{} is {} years old with ${:.2f} as a salary",
                          person.get_name(), person.get_age(), person.get_salary());
  }
};

double calculate_average_eligible_salary_ranges(
    const std::vector<Person>& people, int age_threshold, double min_salary);

#endif  // PERSON_H
