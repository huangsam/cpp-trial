#ifndef FACTORIAL_H
#define FACTORIAL_H

#include <format>
#include <stdexcept>

// Function template for factorial with requires constraint
template <typename T>
  requires std::integral<T>
T factorial(T n) {
  static_assert(sizeof(T) <= sizeof(int64_t),
                "Type too large for factorial computation");
  if (n < 0) {
    throw std::invalid_argument(
        std::format("Factorial input must be non-negative, got: {}", n));
  }
  T result = 1;
  for (T i = 1; i <= n; ++i) {
    result *= i;
  }
  return result;
}

#endif  // FACTORIAL_H
