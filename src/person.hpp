#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>

class Person {
 private:
  std::string name;
  int age;

 public:
  Person(std::string name, int age);

  std::string get_name() const { return name; }
  int get_age() const { return age; }
};

#endif
