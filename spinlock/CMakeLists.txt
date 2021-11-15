cmake_minimum_required(VERSION 3.19)
project(spinlock)

string(APPEND CMAKE_CXX_FLAGS " -std=c++2a")

add_subdirectory(uma)
add_subdirectory(numa)