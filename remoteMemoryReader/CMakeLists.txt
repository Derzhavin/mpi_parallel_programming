cmake_minimum_required(VERSION 3.19)
project(remoteMemoryReader)

set(CMAKE_CXX_STANDARD 20)

if (MSVC)
    set(MPI "C:/Program Files (x86)/Microsoft SDKs/MPI")
endif()

set(MPI_CXX_COMPILER "mpic++")

find_package(MPI REQUIRED)

include_directories(SYSTEM ${MPI_INCLUDE_PATH})

add_executable(mpi_win_create_get main_mpi_win_create_get.cpp)
target_link_libraries(mpi_win_create_get ${MPI_C_LIBRARIES})

add_executable(mpi_win_create_put main_mpi_win_create_put.cpp)
target_link_libraries(mpi_win_create_put ${MPI_C_LIBRARIES})

add_executable(mpi_win_create_get_winlock main_mpi_win_create_get_winlock.cpp)
target_link_libraries(mpi_win_create_get_winlock ${MPI_C_LIBRARIES})

add_executable(mpi_win_create_put_winlock main_mpi_win_create_put_winlock.cpp)
target_link_libraries(mpi_win_create_put_winlock ${MPI_C_LIBRARIES})