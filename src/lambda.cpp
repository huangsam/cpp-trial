#include "lambda.h"

bool lessThan(int a, int b) {
  auto less_than_lambda = [](auto a, auto b) { return a < b; };
  return less_than_lambda(a, b);
}

int sumOfSquares(int a, int b, int c) {
  auto square = [](auto a) { return a * a; };
  auto sum = [](auto a, auto b, auto c) { return a + b + c; };
  return sum(square(a), square(b), square(c));
}
