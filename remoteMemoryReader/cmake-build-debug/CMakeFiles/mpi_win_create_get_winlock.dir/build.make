# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/denis/CLion-2021.1.3/clion-2021.1.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/denis/CLion-2021.1.3/clion-2021.1.3/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /media/denis/Seagate/Projects/mpi_parallel_programming/remoteMemoryReader

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/denis/Seagate/Projects/mpi_parallel_programming/remoteMemoryReader/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/mpi_win_create_get_winlock.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mpi_win_create_get_winlock.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mpi_win_create_get_winlock.dir/flags.make

CMakeFiles/mpi_win_create_get_winlock.dir/main_mpi_win_create_get_winlock.cpp.o: CMakeFiles/mpi_win_create_get_winlock.dir/flags.make
CMakeFiles/mpi_win_create_get_winlock.dir/main_mpi_win_create_get_winlock.cpp.o: ../main_mpi_win_create_get_winlock.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/denis/Seagate/Projects/mpi_parallel_programming/remoteMemoryReader/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mpi_win_create_get_winlock.dir/main_mpi_win_create_get_winlock.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mpi_win_create_get_winlock.dir/main_mpi_win_create_get_winlock.cpp.o -c /media/denis/Seagate/Projects/mpi_parallel_programming/remoteMemoryReader/main_mpi_win_create_get_winlock.cpp

CMakeFiles/mpi_win_create_get_winlock.dir/main_mpi_win_create_get_winlock.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mpi_win_create_get_winlock.dir/main_mpi_win_create_get_winlock.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/denis/Seagate/Projects/mpi_parallel_programming/remoteMemoryReader/main_mpi_win_create_get_winlock.cpp > CMakeFiles/mpi_win_create_get_winlock.dir/main_mpi_win_create_get_winlock.cpp.i

CMakeFiles/mpi_win_create_get_winlock.dir/main_mpi_win_create_get_winlock.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mpi_win_create_get_winlock.dir/main_mpi_win_create_get_winlock.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/denis/Seagate/Projects/mpi_parallel_programming/remoteMemoryReader/main_mpi_win_create_get_winlock.cpp -o CMakeFiles/mpi_win_create_get_winlock.dir/main_mpi_win_create_get_winlock.cpp.s

# Object files for target mpi_win_create_get_winlock
mpi_win_create_get_winlock_OBJECTS = \
"CMakeFiles/mpi_win_create_get_winlock.dir/main_mpi_win_create_get_winlock.cpp.o"

# External object files for target mpi_win_create_get_winlock
mpi_win_create_get_winlock_EXTERNAL_OBJECTS =

mpi_win_create_get_winlock: CMakeFiles/mpi_win_create_get_winlock.dir/main_mpi_win_create_get_winlock.cpp.o
mpi_win_create_get_winlock: CMakeFiles/mpi_win_create_get_winlock.dir/build.make
mpi_win_create_get_winlock: /usr/local/lib/libmpi.so
mpi_win_create_get_winlock: CMakeFiles/mpi_win_create_get_winlock.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/denis/Seagate/Projects/mpi_parallel_programming/remoteMemoryReader/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable mpi_win_create_get_winlock"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mpi_win_create_get_winlock.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mpi_win_create_get_winlock.dir/build: mpi_win_create_get_winlock

.PHONY : CMakeFiles/mpi_win_create_get_winlock.dir/build

CMakeFiles/mpi_win_create_get_winlock.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mpi_win_create_get_winlock.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mpi_win_create_get_winlock.dir/clean

CMakeFiles/mpi_win_create_get_winlock.dir/depend:
	cd /media/denis/Seagate/Projects/mpi_parallel_programming/remoteMemoryReader/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/denis/Seagate/Projects/mpi_parallel_programming/remoteMemoryReader /media/denis/Seagate/Projects/mpi_parallel_programming/remoteMemoryReader /media/denis/Seagate/Projects/mpi_parallel_programming/remoteMemoryReader/cmake-build-debug /media/denis/Seagate/Projects/mpi_parallel_programming/remoteMemoryReader/cmake-build-debug /media/denis/Seagate/Projects/mpi_parallel_programming/remoteMemoryReader/cmake-build-debug/CMakeFiles/mpi_win_create_get_winlock.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mpi_win_create_get_winlock.dir/depend

