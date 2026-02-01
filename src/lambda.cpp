#include "lambda.h"

#include <numeric>

bool less_than(const ValueOne val_one, const ValueTwo val_two) {
  return [](const int val_i, const int val_j) constexpr {
    return val_i < val_j;
  }(val_one.value, val_two.value);
}

int sum_of_squares(std::vector<int> numbers) {
  auto add_square = [](const int accu, const int val_int) constexpr {
    return accu + val_int * val_int;
  };

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
