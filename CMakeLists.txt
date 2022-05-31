cmake_minimum_required(VERSION 3.10)

project(creatortools)
add_subdirectory(generate_libs)
add_executable (generate_tests tests/all_in_one_test.cpp)
target_link_libraries(generate_tests PUBLIC generate_libs)
target_include_directories(generate_tests PUBLIC "${PROJECT_SOURCE_DIR}/generate_libs")
add_custom_command(TARGET generate_tests POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources)