cmake_minimum_required(VERSION 3.19)
project(remoteMemoryReader)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

find_package(MPI REQUIRED)


add_executable(mpi_rma_list_docs main_mpi_rma_list_docs.cpp)
target_link_libraries(mpi_rma_list_docs ${MPI_C_LIBRARIES})

add_executable(mpi_rma_list main_mpi_rma_list.cpp)
target_link_libraries(mpi_rma_list ${MPI_C_LIBRARIES})