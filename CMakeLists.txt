cmake_minimum_required(VERSION 3.2)
project(chromatron_cpp_solver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x -lm")

set(SOURCE_FILES main.cpp)
add_executable(chromatron_cpp_solver ${SOURCE_FILES} device_type.h color_type.h Device.h Device.cpp Cell.cpp Cell.h Ray.cpp Ray.h)