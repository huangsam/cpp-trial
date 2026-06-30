###
# Test setup:
# https://google.github.io/googletest/quickstart-cmake.html
# https://cmake.org/cmake/help/latest/module/FetchContent.html
# https://github.com/google/googletest/releases
###

# enable_testing() is called by the root include(CTest)
# Download and build Google Test framework
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add test files and libraries to the test executable
add_executable(
  test.out

  # Test code
  advanced/factorial_test.cpp
  advanced/lambda_test.cpp
  advanced/template_meta_test.cpp
  concurrency/async_simple_test.cpp
  concurrency/safe_counter_test.cpp
  concurrency/thread_simple_test.cpp
  hello_test.cpp
  memory/memory_management_test.cpp
  memory/move_semantics_test.cpp
  memory/smart_pointers_test.cpp
  oop/inheritance_test.cpp
  oop/person_test.cpp
  stl/date_test.cpp
  stl/file_io_test.cpp
  stl/stl_deep_dive_test.cpp
  types/enums_unions_test.cpp
  types/namespaces_test.cpp
  types/type_safety_test.cpp
)
target_link_libraries(test.out PRIVATE gtest_main cpp_trial_core project_options)

# Suppress warnings from googletest headers (treat as system headers)
target_include_directories(test.out SYSTEM PRIVATE ${gtest_SOURCE_DIR}/include ${gtest_main_SOURCE_DIR}/include)

set_target_properties(test.out PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Clang-Tidy integration
if(WITH_CLANG_TIDY)
  set_target_properties(test.out PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
endif()

# Find all tests and register them with CTest
include(GoogleTest)
gtest_discover_tests(test.out)
