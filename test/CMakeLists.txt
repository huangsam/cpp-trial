###
# Test setup:
# https://google.github.io/googletest/quickstart-cmake.html
###

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/b514bdc898e2951020cbdca1304b75f5950d1f59.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  test.out
  date_test.cpp
  factorial_test.cpp
  hello_test.cpp
  lambda_test.cpp
  person_test.cpp

  # Use CMAKE_SOURCE_DIR as the top level directory
  # https://cmake.org/cmake/help/latest/variable/CMAKE_SOURCE_DIR.html
  ${CMAKE_SOURCE_DIR}/src/date.cpp
  ${CMAKE_SOURCE_DIR}/src/factorial.cpp
  ${CMAKE_SOURCE_DIR}/src/lambda.cpp
  ${CMAKE_SOURCE_DIR}/src/person.cpp
)
target_link_libraries(
  test.out
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(test.out)
