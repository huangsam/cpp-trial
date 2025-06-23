#ifndef THREAD_SIMPLE_H
#define THREAD_SIMPLE_H

#include <string>
#include <thread>

class ThreadSimpleClass {
 public:
  ThreadSimpleClass();
  ~ThreadSimpleClass();

  void start_worker_thread();
  void join_worker_thread();
  [[nodiscard]] std::string get_worker_message() const;
  [[nodiscard]] bool is_worker_finished() const;

 private:
  void worker_function();

  std::thread m_worker_thread;
  std::string m_worker_message;
  bool m_worker_finished;
};

#endif // THREAD_SIMPLE_H
