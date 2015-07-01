cmake_minimum_required(VERSION 3.2)
project(chromatron_cpp_solver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++0x -std=gnu++0x -lm")

set(SOURCE_FILES main.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
add_executable(chroma.exe ${SOURCE_FILES})