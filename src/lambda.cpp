#include "lambda.h"

#include <numeric>

bool less_than(const ValueOne a, const ValueTwo b) {
  return [](const int i, const int j) { return i < j; }(a.value, b.value);
}

int sum_of_squares(std::vector<int> numbers) {
  auto add_square = [](const int acc, const int i) { return acc + (i * i); };

  /**
   * We use std::accumulate here to ensure that we get a consistent
   * output, albeit with less performance. Assuming that we have a larger
   * number of inputs, and associativity and commutativity are upheld, then
   * std::reduce or std::transform_reduce are scalable. To learn more:
   *
   * https://stackoverflow.com/q/47144083
   */
  return std::accumulate(numbers.begin(), numbers.end(), 0, add_square);
}
