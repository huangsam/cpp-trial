#include "safe_counter.h"

SafeCounter::SafeCounter() : count_(0), all_workers_finished_(false) {}

void SafeCounter::start_worker_threads(const int num_threads,
                                       int increments_per_thread) {
  all_workers_finished_ = false;  // Reset for a new run
  count_ = 0;                     // Reset counter

  worker_threads_.clear();  // Clear any previous threads

  for (int i = 0; i < num_threads; ++i) {
    worker_threads_.emplace_back(&SafeCounter::worker_function, this,
                                 increments_per_thread);
  }
}

void SafeCounter::join_worker_threads() {
  for (std::thread& w_th : worker_threads_) {
    if (w_th.joinable()) {
      w_th.join();
    }
  }
  all_workers_finished_ = true;  // All threads have joined
}

void SafeCounter::worker_function(const int increments) {
  for (int i = 0; i < increments; ++i) {
    // --- CRITICAL SECTION START ---
    // Lock the mutex before accessing the shared resource (count_)
    std::lock_guard lock(mutex_);
    count_++;
    // --- CRITICAL SECTION END ---
  }
}

int64_t SafeCounter::get_count() const {
  // While reading a long might be atomic on some architectures,
  // if other threads were still writing, we'd want to ensure
  // we get a consistent read. For a final read after joining,
  // a mutex isn't strictly necessary for correctness, but often good for
  // consistency. However, since we join all threads, the value is stable.
  return count_;
}

bool SafeCounter::are_workers_finished() const {
  return all_workers_finished_.load();  // Use load() for atomic variable
}
