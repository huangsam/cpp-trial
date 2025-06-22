# Set min version of 3.24 to avoid DOWNLOAD_EXTRACT_TIMESTAMP warning
# https://github.com/ethereum/solidity/pull/13429
cmake_minimum_required(VERSION 3.24)

project(
  CPPTrial
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

# Run steps for building main.out
add_subdirectory(src)

# Run steps for building test.out
add_subdirectory(test)

# Define 'format' target
# Find all C++ source and header files in src and test directories
file(GLOB_RECURSE CXX_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/*.hpp
)

# Choose formatting style based on preferences:
# https://clang.llvm.org/docs/ClangFormatStyleOptions.html#basedonstyle
add_custom_target(format
    COMMAND clang-format -i ${CXX_SOURCE_FILES}
    COMMENT "Applying clang-format to source files."
)

# Lint the entire codebase
# https://cppcheck.sourceforge.io/
add_custom_target(lint
    COMMAND cppcheck ${CXX_SOURCE_FILES}
    COMMENT "Linting codebase with cppcheck."
)
