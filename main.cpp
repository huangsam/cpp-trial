#include <iostream>

#include "date.h"
#include "factorial.h"
#include "person.h"

using namespace std;

void printDate(Date d) {
  cout << d.getYear() << "/" << d.getMonth() << "/" << d.getDay() << "\n";
}

void printPerson(Person p) {
  cout << p.getName() << " is " << p.getAge() << " years old\n";
}

int main() {
  // date.h test
  auto d1 = Date(2024, 1, 1);
  printDate(d1);

  // factorial.h test
  cout << "factorial(4): " << factorial(4) << endl;

  // person.h test
  auto p1 = Person("David", 21);
  printPerson(p1);

  return 0;
}
