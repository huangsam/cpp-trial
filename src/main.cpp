#include <iostream>
#include <vector>

#include "date.h"
#include "factorial.h"
#include "lambda.h"
#include "person.h"

using namespace std;

void print_date(Date d) {
  cout << d.get_year() << "/" << d.get_month() << "/" << d.get_day() << "\n";
}

void print_person(Person p) {
  cout << p.get_name() << " is " << p.get_age() << " years old\n";
}

int main() {
  // date.h demo
  auto d1 = Date(2024, 1, 1);
  print_date(d1);
  auto d2 = Date(2024, 2, 2);
  print_date(d2);
  if (d1 < d2) {
    cout << "First date is older than second date\n";
  }

  // factorial.h demo
  cout << "factorial(4): " << factorial(4) << endl;

  // lambda.h demo
  cout << "less_than(3,4): " << less_than(3, 4) << endl;
  cout << "sum_of_squares(vector{1,2,3}): "
       << sum_of_squares(std::vector{1, 2, 3}) << endl;

  // person.h demo
  auto p1 = Person("David", 21);
  print_person(p1);

  return 0;
}
