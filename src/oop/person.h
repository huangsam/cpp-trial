#ifndef PERSON_H
#define PERSON_H

#include <format>
#include <stdexcept>
#include <string>
#include <vector>

// Age represents a validated age value (minimum 1).
struct Age {
  static constexpr int MIN_AGE = 1;
  explicit Age(const int age) : value(age) {
    if (value < MIN_AGE) {
      throw std::invalid_argument(
          std::format("Age must be at least {}, got: {}", MIN_AGE, age));
    }
  }
  int value;
};

// Salary represents a validated non-negative salary value.
struct Salary {
  static constexpr double MIN_SALARY = 0.0;
  explicit Salary(const double salary) : value(salary) {
    if (value < MIN_SALARY) {
      throw std::invalid_argument(
          std::format("Salary must be non-negative, got: {:.2f}", salary));
    }
  }
  double value;
};

// Person represents a human with name, age, and salary information.
class Person {
  std::string name_;
  int age_;
  double salary_;

 public:
  Person(std::string name, Age age, Salary salary);

  [[nodiscard]] std::string get_name() const { return name_; }
  [[nodiscard]] int get_age() const { return age_; }
  [[nodiscard]] double get_salary() const { return salary_; }
};

// Specialization for Person
template <>
struct std::formatter<Person> : std::formatter<std::string> {
  static auto format(const Person& person, std::format_context& ctx) {
    // Using a format specifier for floating-point numbers (:.2f)
    return std::format_to(
        ctx.out(), "{} is {} years old with ${:.2f} as a salary",
        person.get_name(), person.get_age(), person.get_salary());
  }
};

// calculate_average_eligible_salary_ranges computes the average salary for
// people meeting both age and salary thresholds.
double calculate_average_eligible_salary_ranges(
    const std::vector<Person>& people, int age_threshold, double min_salary);

#endif  // PERSON_H
