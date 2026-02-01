###
# Basic setup:
# https://cmake.org/cmake/help/latest/guide/tutorial/index.html
#
# For more about libraries:
# https://cmake.org/cmake/help/latest/command/add_library.html
# https://cmake.org/cmake/help/latest/command/target_include_directories.html
# https://cmake.org/cmake/help/latest/command/target_link_libraries.html
###

# Add all source files to the library
add_library(
  cpp_trial_core STATIC
  date.cpp date.h
  factorial.h
  lambda.cpp lambda.h
  person.cpp person.h
  safe_counter.cpp safe_counter.h
  thread_simple.cpp thread_simple.h
  async_simple.cpp async_simple.h
  inheritance.cpp inheritance.h
  file_io.cpp file_io.h
  enums_unions.cpp enums_unions.h
  namespaces.cpp namespaces.h
  stl_deep_dive.cpp stl_deep_dive.h
  smart_pointers.cpp smart_pointers.h
  type_safety.cpp type_safety.h
  move_semantics.cpp move_semantics.h
  template_meta.cpp template_meta.h
  memory_management.cpp memory_management.h
)
target_include_directories(cpp_trial_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Add entrypoint and library to the main executable
add_executable(main.out main.cpp)
target_link_libraries(main.out cpp_trial_core)
set_target_properties(main.out PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
