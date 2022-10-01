cmake_minimum_required(VERSION 3.10)

add_library(minizip SHARED IMPORTED)

set_target_properties(minizip PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/headers" IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/libs/minizip.so")
