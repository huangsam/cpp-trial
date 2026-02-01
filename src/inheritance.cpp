#include "inheritance.h"

std::string make_animal_speak(const Animal& animal) {
  return animal.get_name() + " says: " + animal.speak();
}
