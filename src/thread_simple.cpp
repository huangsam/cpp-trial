#include "thread_simple.h"

#include <chrono>

ThreadSimpleClass::ThreadSimpleClass() : m_worker_finished(false) {
  // Constructor doesn't start the thread automatically, allowing for controlled
  // testing.
}

ThreadSimpleClass::~ThreadSimpleClass() {
  if (m_worker_thread.joinable()) {
    m_worker_thread.join();
  }
}

void ThreadSimpleClass::start_worker_thread() {
  // Pass 'this' to the worker function so it can modify member variables
  m_worker_thread = std::thread(&ThreadSimpleClass::worker_function, this);
}

void ThreadSimpleClass::join_worker_thread() {
  if (m_worker_thread.joinable()) {
    m_worker_thread.join();
  }
}

void ThreadSimpleClass::worker_function() {
  // Simulate some work
  std::this_thread::sleep_for(
      std::chrono::milliseconds(10));  // Simulate a small delay
  m_worker_message = "Hello from the worker thread!";
  m_worker_finished = true;
  // std::cout << "Worker thread finished its task." << std::endl; // For
  // observation
}

std::string ThreadSimpleClass::get_worker_message() const {
  return m_worker_message;
}

bool ThreadSimpleClass::is_worker_finished() const { return m_worker_finished; }
