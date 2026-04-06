#ifndef LAMBDA_H
#define LAMBDA_H

#include <vector>

// ValueOne wraps a single integer value for comparison operations.
struct ValueOne {
  explicit ValueOne(const int one) : value(one) {}
  int value;
};

// ValueTwo wraps a single integer value for comparison operations.
struct ValueTwo {
  explicit ValueTwo(const int two) : value(two) {}
  int value;
};

// less_than compares two values using a lambda expression.
bool less_than(ValueOne val_one, ValueTwo val_two);

// sum_of_squares computes the sum of squared values in a vector.
int sum_of_squares(std::vector<int> numbers);

#endif  // LAMBDA_H
