#include "lambda.h"

bool lessThan(int a, int b) {
  auto less_than_lambda = [](auto a, auto&& b) { return a < b; };
  return less_than_lambda(a, b);
}
