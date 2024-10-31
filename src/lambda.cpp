#include "lambda.h"

#include <numeric>
#include <vector>

bool less_than(int a, int b) {
  auto check_both = [](int a, int b) { return a < b; };
  return check_both(a, b);
}

int sum_of_squares(std::vector<int> numbers) {
  auto add_square = [](int acc, int i) { return acc + (i * i); };

  /**
   * std::reduce works as expected, given that associativity and
   * commutativity holds for addition and multiplication.
   * Otherwise, we would use std::accumulate to ensure that we
   * get a consistent output, albeit with less performance.
   *
   * https://stackoverflow.com/q/47144083
   */
  return std::reduce(numbers.begin(), numbers.end(), 0, add_square);
}
