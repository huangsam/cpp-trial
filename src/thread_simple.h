#ifndef CONCURRENCY_H
#define CONCURRENCY_H

#include <string>
#include <thread>

class ExampleThreadClass {
 public:
  ExampleThreadClass();
  ~ExampleThreadClass();

  // Public methods in snake_case
  void start_worker_thread();
  void join_worker_thread();
  std::string get_worker_message() const;
  bool is_worker_finished() const;

 private:
  // Private method in snake_case
  void worker_function();

  std::thread m_worker_thread;
  std::string m_worker_message;
  bool m_worker_finished;
};

#endif
