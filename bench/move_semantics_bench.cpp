#include <benchmark/benchmark.h>
#include <memory/move_semantics.h>

// Benchmark deep copy of ResourceManager
static void BM_ResourceManagerCopy(benchmark::State& state) {
  ResourceManager source(state.range(0));
  for (auto _ : state) {
    ResourceManager copy(source);
    benchmark::DoNotOptimize(copy);
  }
}
BENCHMARK(BM_ResourceManagerCopy)->Range(1000, 1000000);

// Benchmark move of ResourceManager
static void BM_ResourceManagerMove(benchmark::State& state) {
  size_t size = state.range(0);
  for (auto _ : state) {
    state.PauseTiming();
    ResourceManager source(size);
    state.ResumeTiming();
    ResourceManager moved(std::move(source));
    benchmark::DoNotOptimize(moved);
  }
}
BENCHMARK(BM_ResourceManagerMove)->Range(1000, 1000000);

BENCHMARK_MAIN();
