include(FetchContent)

# Prevent Google Benchmark from running its own internal tests
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
# Disable examples to speed up build
set(BENCHMARK_ENABLE_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        v1.9.5
)

FetchContent_MakeAvailable(googlebenchmark)

# 1. Memory Management Bench
add_executable(memory_bench.out memory_management_bench.cpp)
target_link_libraries(memory_bench.out PRIVATE benchmark::benchmark_main cpp_trial_core)
set_target_properties(memory_bench.out PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 2. Concurrency Bench
add_executable(concurrency_bench.out concurrency_bench.cpp)
target_link_libraries(concurrency_bench.out PRIVATE benchmark::benchmark_main cpp_trial_core)
set_target_properties(concurrency_bench.out PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 3. Move Semantics Bench
add_executable(move_bench.out move_semantics_bench.cpp)
target_link_libraries(move_bench.out PRIVATE benchmark::benchmark_main cpp_trial_core)
set_target_properties(move_bench.out PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
