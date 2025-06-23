###
# Test setup:
# https://google.github.io/googletest/quickstart-cmake.html
# https://cmake.org/cmake/help/latest/module/FetchContent.html
# https://github.com/google/googletest/releases
###

# Download and build Google Test framework
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add test files and libraries to the test executable
add_executable(
  test.out

  # Test code
  date_test.cpp
  factorial_test.cpp
  hello_test.cpp
  lambda_test.cpp
  person_test.cpp
  thread_simple_test.cpp
)
target_link_libraries(test.out gtest_main cpp_trial_core)

# Find all tests and register them with CTest
include(GoogleTest)
gtest_discover_tests(test.out)
