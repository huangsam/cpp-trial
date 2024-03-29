#include <iostream>
#include <vector>

#include "date.h"
#include "factorial.h"
#include "lambda.h"
#include "person.h"

using namespace std;

void printDate(Date d) {
  cout << d.getYear() << "/" << d.getMonth() << "/" << d.getDay() << "\n";
}

void printPerson(Person p) {
  cout << p.getName() << " is " << p.getAge() << " years old\n";
}

int main() {
  // date.h demo
  auto d1 = Date(2024, 1, 1);
  printDate(d1);
  auto d2 = Date(2024, 2, 2);
  printDate(d2);
  if (d1 < d2) {
    cout << "First date is older than second date\n";
  }

  // factorial.h demo
  cout << "factorial(4): " << factorial(4) << endl;

  // lambda.h demo
  cout << "lessThan(3,4): " << lessThan(3, 4) << endl;
  cout << "sumOfSquares(vector{1,2,3}): " << sumOfSquares(std::vector{1, 2, 3})
       << endl;

  // person.h demo
  auto p1 = Person("David", 21);
  printPerson(p1);

  return 0;
}
