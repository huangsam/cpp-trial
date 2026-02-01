#ifndef FACTORIAL_H
#define FACTORIAL_H

#include <format>
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
