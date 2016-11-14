cmake_minimum_required(VERSION 3.6)
PROJECT(cpp_cross_platform)

# C++ 11
SET(CMAKE_CXX_STANDARD 11)

# Output Directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)
add_subdirectory(test)