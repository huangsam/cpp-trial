#include "async_simple.h"

#include <chrono>
#include <thread>

constexpr long long GREET_SLEEP_MS = 100;

std::string greet() {
  // Simulate some work being done in the background
  std::this_thread::sleep_for(std::chrono::milliseconds(GREET_SLEEP_MS));
  return "Hello, World! from std::async";
}
