#ifndef INHERITANCE_H
#define INHERITANCE_H

#include <string>

// Animal is the base class demonstrating inheritance and virtual polymorphism.
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

// Dog is a derived class that speaks "Woof!".
class Dog : public Animal {
 public:
  explicit Dog(std::string name) : Animal(std::move(name)) {}

  [[nodiscard]] std::string speak() const override { return "Woof!"; }
};

// Cat is a derived class that speaks "Meow!".
class Cat : public Animal {
 public:
  explicit Cat(std::string name) : Animal(std::move(name)) {}

  [[nodiscard]] std::string speak() const override { return "Meow!"; }
};

// make_animal_speak demonstrates polymorphism by calling virtual method on base
// class reference.
std::string make_animal_speak(const Animal& animal);

#endif  // INHERITANCE_H
