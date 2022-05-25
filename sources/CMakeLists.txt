cmake_minimum_required(VERSION 3.22)
project(Ex5_A)

set(CMAKE_CXX_STANDARD 14)

add_executable(Ex5_A Node.hpp)
add_executable(Ex5_A IterationOrder.hpp)
add_executable(Ex5_A CharIterator.cpp CharIterator.hpp)
add_executable(Ex5_A OrgChart.cpp OrgChart.hpp)