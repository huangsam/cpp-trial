#include <benchmark/benchmark.h>

#include <atomic>
#include <mutex>

/**
 * Concurrency Benchmarks
 *
 * These benchmarks compare different synchronization approaches for shared
 * counters:
 * - Mutex: Thread-safe but expensive due to locking overhead
 * - Atomic: Lock-free operations, scales better with contention
 * - Unsafe: No synchronization (for baseline performance measurement only)
 *
 * Key concepts demonstrated:
 * - Mutex contention overhead increases with thread count
 * - Atomic operations provide better scalability
 * - Trade-offs between safety and performance
 */

// Shared counters with proper synchronization
static std::atomic<int64_t> shared_atomic_count(0);
static int64_t shared_mutex_count = 0;
static std::mutex shared_mutex;

// 1. Mutex-protected counter (shared state)
// Demonstrates the cost of mutex contention in high-frequency operations
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
// Test scaling from 1 to 8 threads to show contention effects
BENCHMARK(BM_MutexCounter)->ThreadRange(1, 8)->Repetitions(3);

// 2. Atomic counter (shared state)
// Shows lock-free performance using atomic operations
static void BM_AtomicCounter(benchmark::State& state) {
  if (state.thread_index() == 0) {
    shared_atomic_count = 0;  // Reset only on main thread
  }

  for (auto _ : state) {
    shared_atomic_count++;
  }

  benchmark::DoNotOptimize(shared_atomic_count.load());
}
// Test scaling to show how atomics handle contention better than mutexes
BENCHMARK(BM_AtomicCounter)->ThreadRange(1, 8)->Repetitions(3);

// 3. Unsafe counter (shared state, no protection) - Baseline for hardware speed
// WARNING: This is intentionally unsafe - demonstrates maximum hardware speed
// without any synchronization. Only use for performance comparison!
static void BM_UnsafeCounter(benchmark::State& state) {
  if (state.thread_index() == 0) {
    shared_mutex_count =
        0;  // Reset only on main thread (reuse shared_mutex_count for unsafe)
  }

  for (auto _ : state) {
    shared_mutex_count++;  // Intentionally unsafe - no synchronization
  }

  benchmark::DoNotOptimize(shared_mutex_count);
}
// Shows theoretical maximum performance (single-threaded equivalent)
BENCHMARK(BM_UnsafeCounter)->ThreadRange(1, 8)->Repetitions(3);

// 4. Read-heavy workload comparison
// Demonstrates different behavior under read-heavy vs write-heavy workloads
static std::atomic<int64_t> read_heavy_atomic(0);
static int64_t read_heavy_mutex = 0;
static std::mutex read_heavy_mutex_lock;

static void BM_ReadHeavyMutex(benchmark::State& state) {
  if (state.thread_index() == 0) {
    read_heavy_mutex = 42;  // Initialize with a value
  }

  for (auto _ : state) {
    std::lock_guard<std::mutex> lock(read_heavy_mutex_lock);
    int64_t value = read_heavy_mutex;
    benchmark::DoNotOptimize(value);
  }
}
BENCHMARK(BM_ReadHeavyMutex)->ThreadRange(1, 8)->Repetitions(3);

static void BM_ReadHeavyAtomic(benchmark::State& state) {
  if (state.thread_index() == 0) {
    read_heavy_atomic = 42;  // Initialize with a value
  }

  for (auto _ : state) {
    int64_t value = read_heavy_atomic.load();
    benchmark::DoNotOptimize(value);
  }
}
BENCHMARK(BM_ReadHeavyAtomic)->ThreadRange(1, 8)->Repetitions(3);

BENCHMARK_MAIN();
