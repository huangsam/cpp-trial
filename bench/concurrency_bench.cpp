#include <benchmark/benchmark.h>

#include <atomic>
#include <mutex>

// Shared counters with proper synchronization
static std::atomic<int64_t> shared_atomic_count(0);
static int64_t shared_mutex_count = 0;
static std::mutex shared_mutex;

// 1. Mutex-protected counter (shared state)
static void BM_MutexCounter(benchmark::State& state) {
  if (state.thread_index() == 0) {
    shared_mutex_count = 0;  // Reset only on main thread
  }

  for (auto _ : state) {
    std::lock_guard<std::mutex> lock(shared_mutex);
    shared_mutex_count++;
  }

  benchmark::DoNotOptimize(shared_mutex_count);
}
BENCHMARK(BM_MutexCounter)->ThreadRange(1, 8)->Repetitions(3);

// 2. Atomic counter (shared state)
static void BM_AtomicCounter(benchmark::State& state) {
  if (state.thread_index() == 0) {
    shared_atomic_count = 0;  // Reset only on main thread
  }

  for (auto _ : state) {
    shared_atomic_count++;
  }

  benchmark::DoNotOptimize(shared_atomic_count.load());
}
BENCHMARK(BM_AtomicCounter)->ThreadRange(1, 8)->Repetitions(3);

// 3. Unsafe counter (shared state, no protection) - Baseline for hardware speed
static void BM_UnsafeCounter(benchmark::State& state) {
  if (state.thread_index() == 0) {
    shared_mutex_count = 0;  // Reset only on main thread (reuse shared_mutex_count for unsafe)
  }

  for (auto _ : state) {
    shared_mutex_count++;  // Intentionally unsafe - no synchronization
  }

  benchmark::DoNotOptimize(shared_mutex_count);
}
BENCHMARK(BM_UnsafeCounter)->ThreadRange(1, 8)->Repetitions(3);

BENCHMARK_MAIN();
