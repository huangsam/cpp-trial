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
  hello_test.cpp
  factorial_test.cpp
  ${CMAKE_SOURCE_DIR}/src/factorial.cpp
)
target_link_libraries(
  test.out
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(test.out)
