#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>

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

#endif
