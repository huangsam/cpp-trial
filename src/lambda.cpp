#include "lambda.h"

#include <vector>

bool lessThan(int a, int b) {
  auto less_than_lambda = [](auto a, auto b) { return a < b; };
  return less_than_lambda(a, b);
}

int sumOfSquares(std::vector<int> numbers) {
  auto square = [](auto a) { return a * a; };
  auto sum = 0;
  for (auto i : numbers) {
    sum += square(i);
  }
  return sum;
}
