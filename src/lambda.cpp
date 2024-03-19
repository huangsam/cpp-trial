#include "lambda.h"

#include <algorithm>
#include <vector>

bool lessThan(int a, int b) {
  auto less_than_lambda = [](auto a, auto b) { return a < b; };
  return less_than_lambda(a, b);
}

int sumOfSquares(std::vector<int> numbers) {
  auto square = [](auto acc, auto i) { return acc + (i * i); };
  return std::reduce(numbers.begin(), numbers.end(), 0, square);
}
