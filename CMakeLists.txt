cmake_minimum_required(VERSION 3.6)
PROJECT(cpp_cross_platform)

#Boost
FIND_PACKAGE(Boost)
MESSAGE("Boost_INCLUDE_DIRS ${Boost_INCLUDE_DIRS}")
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
#link_directories(${Boost_LIBRARY_DIRS})

# C++ 11
SET(CMAKE_CXX_STANDARD 11)

# Flags (Trying different ways to enable try/catch/throw with VS2015 and CLang)

#SET(CLANG_COMPILE_FLAGS "-fexceptions")
#add_definitions(${CLANG_COMPILE_FLAGS})
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CLANG_COMPILE_FLAGS}")
#target_compile_options(first-test PRIVATE -fexceptions)

# Output Directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Verbose
#SET (CMAKE_VERBOSE_MAKEFILE 0)

add_subdirectory(src)
add_subdirectory(test)