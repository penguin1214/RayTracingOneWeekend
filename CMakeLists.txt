cmake_minimum_required(VERSION 3.7)
project(RayTracingOneWeekend)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp vec3.cpp vec3.h)
add_executable(RayTracingOneWeekend ${SOURCE_FILES})