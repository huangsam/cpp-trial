#include "safe_counter.h"

#include <chrono>

SafeCounter::SafeCounter() : m_count(0), m_all_workers_finished(false) {}

SafeCounter::~SafeCounter() {
  // Ensure all threads are joined before destruction
  join_worker_threads();
}

void SafeCounter::start_worker_threads(int num_threads,
                                       int increments_per_thread) {
  m_all_workers_finished = false;  // Reset for a new run
  m_count = 0;                     // Reset counter

  m_worker_threads.clear();  // Clear any previous threads

  for (int i = 0; i < num_threads; ++i) {
    m_worker_threads.emplace_back(&SafeCounter::worker_function, this,
                                  increments_per_thread);
  }
}

void SafeCounter::join_worker_threads() {
  for (std::thread& t : m_worker_threads) {
    if (t.joinable()) {
      t.join();
    }
  }
  m_all_workers_finished = true;  // All threads have joined
}

void SafeCounter::worker_function(int increments) {
  for (int i = 0; i < increments; ++i) {
    // --- CRITICAL SECTION START ---
    // Lock the mutex before accessing the shared resource (m_count)
    std::lock_guard<std::mutex> lock(m_mutex);
    m_count++;
    // --- CRITICAL SECTION END ---
  }
}

long SafeCounter::get_count() const {
  // While reading a long might be atomic on some architectures,
  // if other threads were still writing, we'd want to ensure
  // we get a consistent read. For a final read after joining,
  // a mutex isn't strictly necessary for correctness, but often good for
  // consistency. However, since we join all threads, the value is stable.
  return m_count;
}

bool SafeCounter::are_workers_finished() const {
  return m_all_workers_finished.load();  // Use load() for atomic variable
}
