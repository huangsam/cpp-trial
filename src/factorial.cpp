#include "factorial.h"

#include <stdexcept>

auto factorial(const int n) -> int {
  if (n < 0) {
    throw std::invalid_argument("n must be non-negative");
  }
  int result = 1;
  for (int i = 1; i <= n; i++) {
    result *= i;
  }
  return result;
}
