#ifndef SAFE_COUNTER_H
#define SAFE_COUNTER_H

#include <atomic>
#include <mutex>
#include <thread>
#include <vector>

// SafeCounter demonstrates thread-safe counter using mutex and atomic
// variables.
class SafeCounter {
 public:
  SafeCounter();

  void start_worker_threads(int num_threads, int increments_per_thread);
  void join_worker_threads();
  int64_t get_count() const;
  bool are_workers_finished() const;

 private:
  void worker_function(int increments);

  int64_t count_;
  std::mutex mutex_;
  std::vector<std::thread> worker_threads_;
  std::atomic<bool>
      all_workers_finished_;  // To indicate when all threads are done
};

#endif  // SAFE_COUNTER_H
