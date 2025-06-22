#include "person.hpp"

#include <utility>

Person::Person(std::string name, const int age)
    : name(std::move(name)), age(age) {}
