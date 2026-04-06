#include <benchmark/benchmark.h>

#include <atomic>
#include <mutex>

// 1. Mutex-protected counter
static void BM_MutexCounter(benchmark::State& state) {
  static int64_t count = 0;
  static std::mutex m;
  for (auto _ : state) {
    std::lock_guard<std::mutex> lock(m);
    count++;
  }
  benchmark::DoNotOptimize(count);
}
BENCHMARK(BM_MutexCounter)->ThreadRange(1, 8);

// 2. Atomic counter
static void BM_AtomicCounter(benchmark::State& state) {
  static std::atomic<int64_t> count(0);
  for (auto _ : state) {
    count++;
  }
  benchmark::DoNotOptimize(count.load());
}
BENCHMARK(BM_AtomicCounter)->ThreadRange(1, 8);

// 3. Unsafe (No protection) - Baseline for hardware speed
static void BM_UnsafeCounter(benchmark::State& state) {
  int64_t count = 0;
  for (auto _ : state) {
    count++;
  }
  benchmark::DoNotOptimize(count);
}
BENCHMARK(BM_UnsafeCounter);

BENCHMARK_MAIN();
