#include "person.h"

#include <utility>

Person::Person(std::string name, const int age, const double salary)
    : name(std::move(name)), age(age), salary(salary) {}
