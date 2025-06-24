#include "async_simple.h"

#include <chrono>
#include <thread>

std::string greet() {
  // Simulate some work being done in the background
  std::this_thread::sleep_for(
      std::chrono::milliseconds(100));  // Sleep for 100 milliseconds
  return "Hello, World! from std::async";
}
