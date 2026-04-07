#include <benchmark/benchmark.h>
#include <memory/memory_management.h>

#include <vector>

/**
 * Memory Management Benchmarks
 *
 * These benchmarks compare different memory allocation strategies:
 * - Standard new/delete: General-purpose heap allocation
 * - MemoryPool: Bulk allocation for same-sized objects
 * - ArenaAllocator: Region-based allocation with bulk deallocation
 *
 * Key concepts demonstrated:
 * - Memory pools excel at frequent allocation/deallocation of same-sized
 * objects
 * - Arena allocation minimizes fragmentation and provides fast bulk cleanup
 * - Standard allocation has higher overhead but maximum flexibility
 */

// A simple struct to allocate
struct SmallObject {
  int id;
  double value;
  char padding[16];  // Pad to realistic size
};

// Benchmark standard new/delete
// Shows baseline performance of general-purpose heap allocation
static void BM_StandardNewDelete(benchmark::State& state) {
  for (auto _ : state) {
    SmallObject* obj = new SmallObject{42, 3.14, "standard"};
    benchmark::DoNotOptimize(obj);
    delete obj;
  }
}
BENCHMARK(BM_StandardNewDelete)->Repetitions(3);

// Benchmark MemoryPool allocation (allocation-only scenario)
// Demonstrates pool performance when objects have similar lifetimes
static void BM_MemoryPoolAllocate(benchmark::State& state) {
  MemoryPool<SmallObject> pool;
  for (auto _ : state) {
    SmallObject* obj = pool.allocate();
    obj->id = 42;
    obj->value = 3.14;
    benchmark::DoNotOptimize(obj);
    // Note: MemoryPool doesn't support individual deallocation in this
    // implementation
  }
}
BENCHMARK(BM_MemoryPoolAllocate)->Repetitions(3);

// Benchmark MemoryPool allocation/deallocation cycles using new/delete for
// comparison Shows pool efficiency in allocation-heavy scenarios with bulk
// cleanup
static void BM_MemoryPoolCycle(benchmark::State& state) {
  MemoryPool<SmallObject> pool;
  std::vector<SmallObject*> objects;
  objects.reserve(state.range(0));

  for (auto _ : state) {
    // Allocate phase - simulate burst allocation
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
// Test different allocation burst sizes
BENCHMARK(BM_MemoryPoolCycle)->Arg(10)->Arg(100)->Arg(1000)->Repetitions(3);

// Benchmark std::vector with standard allocator
// Shows container performance with default memory management
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
// Test different container sizes
BENCHMARK(BM_VectorStandardAllocator)
    ->Arg(100)
    ->Arg(1000)
    ->Arg(10000)
    ->Repetitions(3);

// Benchmark std::vector with ArenaAllocator
// Demonstrates arena allocation benefits for container-based workloads
static void BM_VectorArenaAllocator(benchmark::State& state) {
  const size_t arena_size = state.range(0) * sizeof(SmallObject) * 2;
  ArenaAllocator arena(arena_size * 2);
  CustomAllocator<SmallObject> alloc(&arena);
  for (auto _ : state) {
    arena.reset();  // Bulk deallocation
    std::vector<SmallObject, CustomAllocator<SmallObject>> v(alloc);
    v.reserve(state.range(0));
    for (int i = 0; i < state.range(0); ++i) {
      v.push_back({i, static_cast<double>(i), "arena"});
    }
    benchmark::DoNotOptimize(v);
  }
}
// Test different container sizes with arena allocation
BENCHMARK(BM_VectorArenaAllocator)
    ->Arg(100)
    ->Arg(1000)
    ->Arg(10000)
    ->Repetitions(3);

// Benchmark allocation patterns: random sizes
// Shows how different allocators handle variable-sized allocation patterns
static void BM_RandomSizeAllocations(benchmark::State& state) {
  std::vector<size_t> sizes = {16, 32, 64, 128, 256, 512, 1024};
  for (auto _ : state) {
    std::vector<void*> allocations;
    allocations.reserve(state.range(0));

    // Allocate objects of random sizes
    for (int i = 0; i < state.range(0); ++i) {
      size_t size = sizes[i % sizes.size()];
      void* ptr = ::operator new(size);
      allocations.push_back(ptr);
    }

    benchmark::DoNotOptimize(allocations);

    // Deallocate
    for (void* ptr : allocations) {
      ::operator delete(ptr);
    }
  }
}
BENCHMARK(BM_RandomSizeAllocations)->Arg(100)->Arg(1000)->Repetitions(3);

BENCHMARK_MAIN();
