cmake_minimum_required(VERSION 3.6)
PROJECT(cpp_cross_platform)

MESSAGE("CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}")

#CONAN
if (${WIN32})
    execute_process(COMMAND ${CMAKE_SOURCE_DIR}/install.bat ${CMAKE_SOURCE_DIR})
endif()

if(EXISTS ${CMAKE_SOURCE_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_SOURCE_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
endif()

#Boost
FIND_PACKAGE(Boost REQUIRED)

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
