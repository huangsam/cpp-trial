#ifndef PERSON_H
#define PERSON_H

#include <format>
#include <string>
#include <vector>

class Person {
  std::string name;
  int age;
  double salary;

 public:
  Person(std::string name, int age, double salary);

  [[nodiscard]] std::string get_name() const { return name; }
  [[nodiscard]] int get_age() const { return age; }
  [[nodiscard]] double get_salary() const { return salary; }
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

double calculate_average_eligible_salary_ranges(
    const std::vector<Person>& people, int age_threshold, double min_salary);

#endif // PERSON_H
