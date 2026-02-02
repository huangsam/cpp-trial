#ifndef THREAD_SIMPLE_H
#define THREAD_SIMPLE_H

#include <string>
#include <thread>

// ThreadSimpleClass manages a background worker thread.
// Demonstrates basic threading, synchronization, and message passing.
class ThreadSimpleClass {
 public:
  ThreadSimpleClass();

  void start_worker_thread();
  void join_worker_thread();
  [[nodiscard]] std::string get_worker_message() const;
  [[nodiscard]] bool is_worker_finished() const;

 private:
  void worker_function();

  std::thread worker_thread_;
  std::string worker_message_;
  bool worker_finished_;
};

#endif  // THREAD_SIMPLE_H
