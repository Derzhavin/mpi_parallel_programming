cmake_minimum_required(VERSION 3.22)
project(rma_list_sketch)

set(CMAKE_CXX_STANDARD 20)

add_executable(node_replacer main_node_replacer.cpp)
add_executable(node_shifter main_node_shifter.cpp)
