#ifndef SAFE_COUNTER_H
#define SAFE_COUNTER_H

#include <atomic>
#include <mutex>
#include <thread>
#include <vector>

class SafeCounter {
 public:
  SafeCounter();
  ~SafeCounter();

  void start_worker_threads(int num_threads, int increments_per_thread);
  void join_worker_threads();
  long get_count() const;
  bool are_workers_finished() const;

 private:
  void worker_function(int increments);

  long m_count;
  std::mutex m_mutex;
  std::vector<std::thread> m_worker_threads;
  std::atomic<bool>
      m_all_workers_finished;  // To indicate when all threads are done
};

#endif // SAFE_COUNTER_H
