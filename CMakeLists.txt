cmake_minimum_required(VERSION 3.10)

project(GlowML)

set(CMAKE_CXX_STANDARD 17)

#include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

#source files
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

#set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_executable(GlowML 
src/main.cpp
src/fileio.cpp
)

