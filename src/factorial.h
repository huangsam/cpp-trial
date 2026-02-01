#ifndef FACTORIAL_H
#define FACTORIAL_H

#include <stdexcept>
#include <type_traits>

template <typename T>
concept Integral = std::is_integral_v<T>;

// Function template for factorial with concept constraint
template <Integral T>
T factorial(T n) {
  static_assert(sizeof(T) <= sizeof(int64_t),
                "Type too large for factorial computation");
  if (n < 0) {
    throw std::invalid_argument("n must be non-negative");
  }
  T result = 1;
  for (T i = 1; i <= n; ++i) {
    result *= i;
  }
  return result;
}

#endif  // FACTORIAL_H
