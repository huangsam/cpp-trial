#include "thread_simple.h"

#include <chrono>

ExampleThreadClass::ExampleThreadClass() : m_worker_finished(false) {
  // Constructor doesn't start the thread automatically, allowing for controlled
  // testing.
}

ExampleThreadClass::~ExampleThreadClass() {
  if (m_worker_thread.joinable()) {
    m_worker_thread.join();
  }
}

void ExampleThreadClass::start_worker_thread() {
  // Pass 'this' to the worker function so it can modify member variables
  m_worker_thread = std::thread(&ExampleThreadClass::worker_function, this);
}

void ExampleThreadClass::join_worker_thread() {
  if (m_worker_thread.joinable()) {
    m_worker_thread.join();
  }
}

void ExampleThreadClass::worker_function() {
  // Simulate some work
  std::this_thread::sleep_for(
      std::chrono::milliseconds(10));  // Simulate a small delay
  m_worker_message = "Hello from the worker thread!";
  m_worker_finished = true;
  // std::cout << "Worker thread finished its task." << std::endl; // For
  // observation
}

std::string ExampleThreadClass::get_worker_message() const {
  return m_worker_message;
}

bool ExampleThreadClass::is_worker_finished() const {
  return m_worker_finished;
}
