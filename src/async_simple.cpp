#include "async_simple.h"

#include <chrono>
#include <thread>

std::string greet() {
  // Simulate some work being done in the background
  std::this_thread::sleep_for(
      std::chrono::milliseconds(2000));  // Sleep for 2 seconds
  return "Hello, World! from std::async";
}
