get_filename_component(project_dir ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${project_dir})

if (MSVC)
    set(MPI "C:/Program Files (x86)/Microsoft SDKs/MPI")
endif()

if (UNIX)
    set(MPI_CXX_COMPILER "mpic++")
endif()

file(GLOB SOURCES "*.cpp" "*.c")

find_package(MPI REQUIRED)

include_directories(SYSTEM ${MPI_INCLUDE_PATH})

add_library(${project_dir} SHARED ${SOURCES})
target_link_libraries(
        ${project_dir}
        ${MPI_CXX_LIBRARIES}
)