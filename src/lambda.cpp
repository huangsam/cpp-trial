#include "lambda.h"

#include <numeric>
#include <vector>

bool lessThan(int a, int b) {
  auto less_than = [](int a, int b) { return a < b; };
  return less_than(a, b);
}

int sumOfSquares(std::vector<int> numbers) {
  auto square = [](int acc, int i) { return acc + (i * i); };
  return std::reduce(numbers.begin(), numbers.end(), 0, square);
}
