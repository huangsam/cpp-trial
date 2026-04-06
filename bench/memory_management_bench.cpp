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
BENCHMARK(BM_StandardNewDelete);

// Benchmark MemoryPool allocation
static void BM_MemoryPoolAllocate(benchmark::State& state) {
    MemoryPool<SmallObject> pool;
    for (auto _ : state) {
        SmallObject* obj = pool.allocate();
        obj->id = 42;
        obj->value = 3.14;
        benchmark::DoNotOptimize(obj);
        // Note: MemoryPool in this implementation doesn't support individual deallocation
    }
}
BENCHMARK(BM_MemoryPoolAllocate);

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
BENCHMARK(BM_VectorStandardAllocator)->Arg(100)->Arg(1000)->Arg(10000);

// Benchmark std::vector with ArenaAllocator
static void BM_VectorArenaAllocator(benchmark::State& state) {
    const size_t arena_size = state.range(0) * sizeof(SmallObject) * 2;
    for (auto _ : state) {
        ArenaAllocator arena(arena_size);
        CustomAllocator<SmallObject> alloc(&arena);
        std::vector<SmallObject, CustomAllocator<SmallObject>> v(alloc);
        v.reserve(state.range(0));
        for (int i = 0; i < state.range(0); ++i) {
            v.push_back({i, static_cast<double>(i), "arena"});
        }
        benchmark::DoNotOptimize(v);
    }
}
BENCHMARK(BM_VectorArenaAllocator)->Arg(100)->Arg(1000)->Arg(10000);

BENCHMARK_MAIN();
