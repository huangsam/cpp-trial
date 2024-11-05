#ifndef PERSON_H
#define PERSON_H

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
