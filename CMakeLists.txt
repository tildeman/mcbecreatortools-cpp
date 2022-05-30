cmake_minimum_required(VERSION 3.10)

project(creatortools)
add_subdirectory(generate_libs)
add_executable (generate_tests generate_libs/all_in_one_test.cpp)
target_link_libraries(generate_tests PUBLIC generate_libs)