cmake_minimum_required(VERSION 3.22)
project(rma_shared_window)

set(CMAKE_CXX_STANDARD 17)

find_package(MPI REQUIRED)
add_executable(${PROJECT_NAME} main_active_rma_shared_win.cpp)
target_link_libraries(${PROJECT_NAME} ${MPI_C_LIBRARIES})