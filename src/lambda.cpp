#include "lambda.h"

#include <numeric>
#include <vector>

bool lessThan(int a, int b) {
  auto less_than = [](int a, int b) { return a < b; };
  return less_than(a, b);
}

int sumOfSquares(std::vector<int> numbers) {
  auto square = [](int acc, int i) { return acc + (i * i); };

  /**
   * std::reduce works as expected, given that associativity and
   * commutativity holds for addition and multiplication.
   * Otherwise, we would use std::accumulate to ensure that we
   * get a consistent output, albeit with less performance.
   *
   * https://stackoverflow.com/q/47144083
   */
  return std::reduce(numbers.begin(), numbers.end(), 0, square);
}
