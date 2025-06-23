###
# Basic setup:
# https://cmake.org/cmake/help/latest/guide/tutorial/index.html
###

# Add all source files to the library
add_library(
  cpp_trial_core STATIC
  date.cpp date.h
  factorial.cpp factorial.h
  lambda.cpp lambda.h
  person.cpp person.h
  safe_counter.cpp safe_counter.h
  thread_simple.cpp thread_simple.h
)
target_include_directories(cpp_trial_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Add entrypoint and library to the main executable
add_executable(main.out main.cpp)
target_link_libraries(main.out cpp_trial_core)
