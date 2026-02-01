#ifndef INHERITANCE_H
#define INHERITANCE_H

#include <string>

// Base class demonstrating inheritance and polymorphism
class Animal {
 public:
  explicit Animal(std::string name) : name_(std::move(name)) {}
  virtual ~Animal() = default;  // Pure virtual destructor for polymorphism

  // Virtual function for polymorphism
  [[nodiscard]] virtual std::string speak() const = 0;

  [[nodiscard]] std::string get_name() const { return name_; }

 private:
  std::string name_;
};

// Derived class: Dog
class Dog : public Animal {
 public:
  explicit Dog(std::string name) : Animal(std::move(name)) {}

  [[nodiscard]] std::string speak() const override { return "Woof!"; }
};

// Derived class: Cat
class Cat : public Animal {
 public:
  explicit Cat(std::string name) : Animal(std::move(name)) {}

  [[nodiscard]] std::string speak() const override { return "Meow!"; }
};

// Function demonstrating polymorphism: takes base reference and calls virtual method
std::string make_animal_speak(const Animal& animal);

#endif  // INHERITANCE_H