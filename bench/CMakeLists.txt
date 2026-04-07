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

# Function to add a benchmark with standard settings
function(add_trial_benchmark target source)
  add_executable(${target}.out ${source})
  target_link_libraries(${target}.out PRIVATE benchmark::benchmark_main cpp_trial_core project_options)
  set_target_properties(${target}.out PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/bench)

  # Clang-Tidy integration
  if(WITH_CLANG_TIDY)
    set_target_properties(${target}.out PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
  endif()
endfunction()

# Memory Management Bench
add_trial_benchmark(memory_bench memory_management_bench.cpp)

# Concurrency Bench
add_trial_benchmark(concurrency_bench concurrency_bench.cpp)

# Move Semantics Bench
add_trial_benchmark(move_bench move_semantics_bench.cpp)
