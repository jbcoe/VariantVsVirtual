cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(CMAKE_CXX_FLAGS "-O3 -finline-functions")

include_directories(external/eggs-variant/include)
include_directories(.)

add_executable(variant variant.cpp)
add_executable(virtual virtual.cpp)

