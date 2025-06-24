#ifndef LAMBDA_H
#define LAMBDA_H

#include <vector>

struct ValueOne {
  explicit ValueOne(const int one) : value(one) {}
  int value;
};

struct ValueTwo {
  explicit ValueTwo(const int two) : value(two) {}
  int value;
};

bool less_than(ValueOne a, ValueTwo b);

int sum_of_squares(std::vector<int> numbers);

#endif // LAMBDA_H
