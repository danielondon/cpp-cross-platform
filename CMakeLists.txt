cmake_minimum_required(VERSION 3.6)
PROJECT(cpp_cross_platform)

#Boost
FIND_PACKAGE(Boost)
MESSAGE("Boost_INCLUDE_DIRS ${Boost_INCLUDE_DIRS}")
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
#link_directories(${Boost_LIBRARY_DIRS})

# C++ 11
SET(CMAKE_CXX_STANDARD 11)

# Flags
#set (CMAKE_CXX_FLAGS "-fexceptions")

# Output Directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Verbose
#SET (CMAKE_VERBOSE_MAKEFILE 0)

add_subdirectory(src)
add_subdirectory(test)