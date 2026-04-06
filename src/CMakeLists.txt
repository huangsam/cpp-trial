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
  stl/date.cpp stl/date.h
  advanced/factorial.h
  advanced/lambda.cpp advanced/lambda.h
  oop/person.cpp oop/person.h
  concurrency/safe_counter.cpp concurrency/safe_counter.h
  concurrency/thread_simple.cpp concurrency/thread_simple.h
  concurrency/async_simple.cpp concurrency/async_simple.h
  oop/inheritance.cpp oop/inheritance.h
  stl/file_io.cpp stl/file_io.h
  types/enums_unions.cpp types/enums_unions.h
  types/namespaces.cpp types/namespaces.h
  stl/stl_deep_dive.cpp stl/stl_deep_dive.h
  memory/smart_pointers.cpp memory/smart_pointers.h
  types/type_safety.cpp types/type_safety.h
  memory/move_semantics.cpp memory/move_semantics.h
  advanced/template_meta.cpp advanced/template_meta.h
  memory/memory_management.cpp memory/memory_management.h
)
target_include_directories(cpp_trial_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Add entrypoint and library to the main executable
add_executable(main.out main.cpp)
target_link_libraries(main.out cpp_trial_core)
set_target_properties(main.out PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
