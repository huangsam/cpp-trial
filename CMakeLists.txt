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

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(src)

# Run steps for building test.out
add_subdirectory(test)
