get_filename_component(project_dir ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${project_dir})

file(GLOB SOURCES "*.cpp" "*.c")

find_package(Threads REQUIRED)

add_executable(${project_dir}_spinlock ${SOURCES})
target_link_libraries(
    ${project_dir}_spinlock
    ${CMAKE_THREAD_LIBS_INIT}
)