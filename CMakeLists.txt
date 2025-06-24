# Set min version of 3.24 to avoid DOWNLOAD_EXTRACT_TIMESTAMP warning
# https://github.com/ethereum/solidity/pull/13429
cmake_minimum_required(VERSION 3.24)

project(
  cpp-trial
  VERSION 1.0
  LANGUAGES CXX
)

# Include CTest
# https://cmake.org/cmake/help/latest/module/CTest.html
include(CTest)

# Set flags for baseline
# https://clang.llvm.org/docs/DiagnosticsReference.html
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Wunused -Werror")

# Set flags for each build type
# https://stackoverflow.com/a/41361741/2748860
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Set standard to C++20
# https://en.cppreference.com/w/cpp/20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the location for all binaries to be under build/bin
# https://stackoverflow.com/q/3431829
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Enable clang-tidy
# https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_CLANG_TIDY.html
# https://stackoverflow.com/a/64252351/2748860
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
option(ENABLE_CLANG_TIDY "Enable Clang-Tidy static analysis" ON)

find_program(CLANG_TIDY_EXEC NAMES clang-tidy)
set(CLANG_TIDY_ARGS ${CLANG_TIDY_EXEC})

if (CLANG_TIDY_EXEC AND ENABLE_CLANG_TIDY)
  set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_ARGS}" CACHE STRING "Clang-Tidy executable and arguments")
  message(STATUS "Clang-Tidy enabled: ${CMAKE_CXX_CLANG_TIDY}")
else ()
  set(CMAKE_CXX_CLANG_TIDY "" CACHE STRING "" FORCE) # Force to empty if explicitly disabled or not found
  message(STATUS "Clang-Tidy disabled")
endif ()

# Run steps for building main.out
add_subdirectory(src)

# Run steps for building test.out
add_subdirectory(test)
