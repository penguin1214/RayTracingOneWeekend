cmake_minimum_required(VERSION 3.6)
project(RayTracingOneWeekend)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(SOURCE_FILES main.cpp vec3.h ray.h hitable.h sphere.h hitable_list.h)
add_executable(RayTracingOneWeekend ${SOURCE_FILES})