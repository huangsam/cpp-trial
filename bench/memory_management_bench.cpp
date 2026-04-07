#include <benchmark/benchmark.h>
#include <memory/memory_management.h>

#include <vector>

// A simple struct to allocate
struct SmallObject {
  int id;
  double value;
  char padding[16];
};

// Benchmark standard new/delete
static void BM_StandardNewDelete(benchmark::State& state) {
  for (auto _ : state) {
    SmallObject* obj = new SmallObject{42, 3.14, "standard"};
    benchmark::DoNotOptimize(obj);
    delete obj;
  }
}
BENCHMARK(BM_StandardNewDelete)->Repetitions(3);

// Benchmark MemoryPool allocation (allocation-only scenario)
static void BM_MemoryPoolAllocate(benchmark::State& state) {
  MemoryPool<SmallObject> pool;
  for (auto _ : state) {
    SmallObject* obj = pool.allocate();
    obj->id = 42;
    obj->value = 3.14;
    benchmark::DoNotOptimize(obj);
    // Note: MemoryPool doesn't support individual deallocation in this implementation
  }
}
BENCHMARK(BM_MemoryPoolAllocate)->Repetitions(3);

// Benchmark MemoryPool allocation/deallocation cycles using new/delete for comparison
static void BM_MemoryPoolCycle(benchmark::State& state) {
  MemoryPool<SmallObject> pool;
  std::vector<SmallObject*> objects;
  objects.reserve(state.range(0));

  for (auto _ : state) {
    // Allocate phase
    for (int i = 0; i < state.range(0); ++i) {
      SmallObject* obj = pool.allocate();
      obj->id = i;
      obj->value = static_cast<double>(i);
      objects.push_back(obj);
    }

    // Simulate "deallocation" by resetting the pool (bulk deallocation)
    benchmark::DoNotOptimize(objects);
    objects.clear();
    // Reset pool for next iteration
    pool.reset();
  }
}
BENCHMARK(BM_MemoryPoolCycle)->Arg(10)->Arg(100)->Arg(1000)->Repetitions(3);

// Benchmark std::vector with standard allocator
static void BM_VectorStandardAllocator(benchmark::State& state) {
  for (auto _ : state) {
    std::vector<SmallObject> v;
    v.reserve(state.range(0));
    for (int i = 0; i < state.range(0); ++i) {
      v.push_back({i, static_cast<double>(i), "vector"});
    }
    benchmark::DoNotOptimize(v);
  }
}
BENCHMARK(BM_VectorStandardAllocator)->Arg(100)->Arg(1000)->Arg(10000)->Repetitions(3);

// Benchmark std::vector with ArenaAllocator
static void BM_VectorArenaAllocator(benchmark::State& state) {
  const size_t arena_size = state.range(0) * sizeof(SmallObject) * 2;
  ArenaAllocator arena(arena_size * 2);
  CustomAllocator<SmallObject> alloc(&arena);
  for (auto _ : state) {
    arena.reset();
    std::vector<SmallObject, CustomAllocator<SmallObject>> v(alloc);
    v.reserve(state.range(0));
    for (int i = 0; i < state.range(0); ++i) {
      v.push_back({i, static_cast<double>(i), "arena"});
    }
    benchmark::DoNotOptimize(v);
  }
}
BENCHMARK(BM_VectorArenaAllocator)->Arg(100)->Arg(1000)->Arg(10000)->Repetitions(3);

BENCHMARK_MAIN();
