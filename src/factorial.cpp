#include "factorial.h"

#include <stdexcept>

int factorial(const int n) {
  if (n < 0) {
    throw std::invalid_argument("n must be non-negative");
  }
  int result = 1;
  for (int i = 1; i <= n; i++) {
    result *= i;
  }
  return result;
}
