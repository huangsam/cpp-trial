#include "thread_simple.h"

#include <chrono>

constexpr int64_t WORK_SLEEP_MS = 10;

ThreadSimpleClass::ThreadSimpleClass() : worker_finished_(false) {
  // Constructor doesn't start the thread automatically, allowing for controlled
  // testing.
}

void ThreadSimpleClass::start_worker_thread() {
  // Pass 'this' to the worker function so it can modify member variables
  worker_thread_ = std::thread(&ThreadSimpleClass::worker_function, this);
}

void ThreadSimpleClass::join_worker_thread() {
  if (worker_thread_.joinable()) {
    worker_thread_.join();
  }
}

void ThreadSimpleClass::worker_function() {
  // Simulate some work
  std::this_thread::sleep_for(std::chrono::milliseconds(WORK_SLEEP_MS));
  worker_message_ = "Hello from the worker thread!";
  worker_finished_ = true;
}

std::string ThreadSimpleClass::get_worker_message() const {
  return worker_message_;
}

bool ThreadSimpleClass::is_worker_finished() const { return worker_finished_; }
