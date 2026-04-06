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

# Add the benchmark executable
add_executable(bench.out
  memory_management_bench.cpp
)

target_link_libraries(bench.out
  PRIVATE
    benchmark::benchmark_main
    cpp_trial_core
)

set_target_properties(bench.out PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
