###
# Basic setup:
# https://cmake.org/cmake/help/latest/guide/tutorial/index.html
###

add_library(CPPTrialCore STATIC date.cpp factorial.cpp lambda.cpp person.cpp)
target_include_directories(CPPTrialCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(main.out main.cpp)
target_link_libraries(main.out PRIVATE CPPTrialCore)
