# Set min version of 3.24 to avoid DOWNLOAD_EXTRACT_TIMESTAMP warning
# https://github.com/ethereum/solidity/pull/13429
cmake_minimum_required(VERSION 3.24)

project(
  cpp-trial
  VERSION 1.0
  LANGUAGES CXX
)

# Options
option(WITH_SANITIZERS "Enable Address and Undefined Behavior Sanitizers" OFF)
option(WITH_CLANG_TIDY "Enable Clang-Tidy static analysis" OFF)
option(ENABLE_LTO "Enable Interprocedural Optimization (LTO)" OFF)

# Include CTest
# https://cmake.org/cmake/help/latest/module/CTest.html
include(CTest)

# Create an INTERFACE library for our specific compiler settings (avoids polluting dependencies)
add_library(project_options INTERFACE)

# Set flags for baseline
# https://clang.llvm.org/docs/DiagnosticsReference.html
target_compile_options(project_options INTERFACE
  -Wall
  -Wextra
  -Wpedantic
  -Wunused
  -Werror
  $<$<CONFIG:Debug>:-g>
  $<$<CONFIG:Release>:-O3>
  $<$<CONFIG:Release>:-DNDEBUG>
)

# Sanitizers
if(WITH_SANITIZERS)
  target_compile_options(project_options INTERFACE -fsanitize=address,undefined)
  target_link_options(project_options INTERFACE -fsanitize=address,undefined)
endif()

# Interprocedural Optimization (LTO)
if(ENABLE_LTO)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT ipo_supported OUTPUT error)
  if(ipo_supported)
    set_property(TARGET project_options PROPERTY INTERFACE_INTERPROCEDURAL_OPTIMIZATION TRUE)
  else()
    message(WARNING "IPO/LTO is not supported: ${error}")
  endif()
endif()

# Clang-Tidy
if(WITH_CLANG_TIDY)
  # Just invoke clang-tidy. It will automatically detect and use the .clang-tidy config file at the root.
  set(CLANG_TIDY_COMMAND "clang-tidy")
endif()

# Set standard to C++20
# https://en.cppreference.com/w/cpp/20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configure test data directory
set(TEST_DATA_DIR "${CMAKE_BINARY_DIR}/test_data")

add_subdirectory(src)

# Run steps for building test.out
add_subdirectory(test)
add_subdirectory(bench)

# Format target
add_custom_target(format
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMAND bash -c "git ls-files '*.cpp' '*.h' | xargs clang-format -i"
  COMMENT "Formatting all source files with clang-format"
  VERBATIM
)
