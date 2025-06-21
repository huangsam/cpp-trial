###
# Test setup:
# https://google.github.io/googletest/quickstart-cmake.html
# https://cmake.org/cmake/help/latest/module/FetchContent.html
# https://github.com/google/googletest/releases
###

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Use CMAKE_SOURCE_DIR as the top level directory
# https://cmake.org/cmake/help/latest/variable/CMAKE_SOURCE_DIR.html
#
# Using globs strategically here. But generally it should be avoided
# as it can introduce unexpected behavior:
# https://www.reddit.com/r/cmake/comments/17j3fmu/comment/k6yb8ej
file(GLOB SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM SRC_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp)

add_executable(
  test.out

  # Test code
  date_test.cpp
  factorial_test.cpp
  hello_test.cpp
  lambda_test.cpp
  person_test.cpp

  # Source code
  ${SRC_FILES}
)
target_link_libraries(
  test.out
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(test.out)
