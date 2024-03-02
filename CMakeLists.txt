###
# Basic setup:
# https://cmake.org/cmake/help/latest/guide/tutorial/index.html
###

cmake_minimum_required(VERSION 3.24)

project(
  CPPTest
  VERSION 1.0
  LANGUAGES CXX
)

set(CMAKE_CXX_FLAGS "-Wall -O3")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
  main.out
  src/main.cpp
  src/date.cpp
  src/factorial.cpp
  src/person.cpp
)

###
# Test setup:
# https://google.github.io/googletest/quickstart-cmake.html
###

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  test.out
  test/hello_test.cpp
  test/factorial_test.cpp
  src/factorial.cpp
)
target_link_libraries(
  test.out
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(test.out)
