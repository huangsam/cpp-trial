#include <benchmark/benchmark.h>
#include <memory/move_semantics.h>

#include <chrono>

/**
 * Move Semantics Benchmarks
 *
 * These benchmarks demonstrate the performance benefits of move semantics
 * vs copy semantics in C++. Move operations avoid expensive deep copies
 * by transferring ownership of resources instead of duplicating them.
 *
 * Key concepts demonstrated:
 * - Copy constructors create expensive deep copies
 * - Move constructors transfer ownership cheaply
 * - Performance difference grows with data size
 */

// Benchmark deep copy of ResourceManager
// This shows the cost of traditional copy semantics - expensive deep copies
static void BM_ResourceManagerCopy(benchmark::State& state) {
  ResourceManager source(state.range(0));
  for (auto _ : state) {
    ResourceManager copy(source);  // Deep copy - expensive!
    benchmark::DoNotOptimize(copy);
  }
}
// Test with different resource sizes to show scaling
BENCHMARK(BM_ResourceManagerCopy)
    ->RangeMultiplier(10)
    ->Range(100, 100000)
    ->Repetitions(3);

// Benchmark move of ResourceManager
// This shows the efficiency of move semantics - cheap ownership transfer
static void BM_ResourceManagerMove(benchmark::State& state) {
  size_t size = state.range(0);
  for (auto _ : state) {
    state.PauseTiming();
    ResourceManager source(size);  // Setup outside timing
    state.ResumeTiming();
    ResourceManager moved(std::move(source));  // Move - cheap!
    benchmark::DoNotOptimize(moved);
  }
}
// Test with different resource sizes to show consistent performance
BENCHMARK(BM_ResourceManagerMove)
    ->RangeMultiplier(10)
    ->Range(100, 100000)
    ->Repetitions(3);

// Benchmark move vs copy performance ratio
// Demonstrates the performance advantage of move semantics
static void BM_MoveVsCopyComparison(benchmark::State& state) {
  size_t size = state.range(0);
  double copy_time_total = 0;
  double move_time_total = 0;
  int iterations = 0;

  for (auto _ : state) {
    // Measure copy time
    auto start_copy = std::chrono::high_resolution_clock::now();
    ResourceManager source(size);
    ResourceManager copied = source;  // Copy
    auto end_copy = std::chrono::high_resolution_clock::now();
    copy_time_total +=
        std::chrono::duration<double>(end_copy - start_copy).count();

    // Measure move time
    auto start_move = std::chrono::high_resolution_clock::now();
    ResourceManager source2(size);
    ResourceManager moved = std::move(source2);  // Move
    auto end_move = std::chrono::high_resolution_clock::now();
    move_time_total +=
        std::chrono::duration<double>(end_move - start_move).count();

    benchmark::DoNotOptimize(copied);
    benchmark::DoNotOptimize(moved);
    iterations++;
  }

  // Report average ratio
  double avg_copy_time = copy_time_total / iterations;
  double avg_move_time = move_time_total / iterations;
  double ratio = avg_copy_time / avg_move_time;

  state.counters["copy/move_ratio"] = benchmark::Counter(ratio);
}
BENCHMARK(BM_MoveVsCopyComparison)
    ->RangeMultiplier(10)
    ->Range(1000, 100000)
    ->Repetitions(5);

BENCHMARK_MAIN();
