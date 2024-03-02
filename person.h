#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person
{
private:
  std::string name;
  int age;

public:
  Person(std::string name, int age);

  std::string getName() const { return name; }
  int getAge() const { return age; }
};

#endif
