# Set min version of 3.24 to avoid DOWNLOAD_EXTRACT_TIMESTAMP warning
# https://github.com/ethereum/solidity/pull/13429
cmake_minimum_required(VERSION 3.24)

project(
  CPPTrial
  VERSION 1.0
  LANGUAGES CXX
)

# Set baseline settings for C++
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

# Set build-specific flags
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Set C++ standard to 2020
# https://en.cppreference.com/w/cpp/20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the location for all binaries to be under build/bin
# https://stackoverflow.com/q/3431829
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Run steps for building main.out
add_subdirectory(src)

# Run steps for building test.out
add_subdirectory(test)
