# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /cygdrive/c/Users/failury/.CLion2018.3/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/failury/.CLion2018.3/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/failury/Desktop/ecs-150-project-1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/failury/Desktop/ecs-150-project-1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ecs_150_project_1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ecs_150_project_1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ecs_150_project_1.dir/flags.make

CMakeFiles/ecs_150_project_1.dir/main.cpp.o: CMakeFiles/ecs_150_project_1.dir/flags.make
CMakeFiles/ecs_150_project_1.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/failury/Desktop/ecs-150-project-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ecs_150_project_1.dir/main.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ecs_150_project_1.dir/main.cpp.o -c /cygdrive/c/Users/failury/Desktop/ecs-150-project-1/main.cpp

CMakeFiles/ecs_150_project_1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ecs_150_project_1.dir/main.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/Users/failury/Desktop/ecs-150-project-1/main.cpp > CMakeFiles/ecs_150_project_1.dir/main.cpp.i

CMakeFiles/ecs_150_project_1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ecs_150_project_1.dir/main.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/Users/failury/Desktop/ecs-150-project-1/main.cpp -o CMakeFiles/ecs_150_project_1.dir/main.cpp.s

# Object files for target ecs_150_project_1
ecs_150_project_1_OBJECTS = \
"CMakeFiles/ecs_150_project_1.dir/main.cpp.o"

# External object files for target ecs_150_project_1
ecs_150_project_1_EXTERNAL_OBJECTS =

ecs_150_project_1.exe: CMakeFiles/ecs_150_project_1.dir/main.cpp.o
ecs_150_project_1.exe: CMakeFiles/ecs_150_project_1.dir/build.make
ecs_150_project_1.exe: CMakeFiles/ecs_150_project_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/failury/Desktop/ecs-150-project-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ecs_150_project_1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ecs_150_project_1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ecs_150_project_1.dir/build: ecs_150_project_1.exe

.PHONY : CMakeFiles/ecs_150_project_1.dir/build

CMakeFiles/ecs_150_project_1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ecs_150_project_1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ecs_150_project_1.dir/clean

CMakeFiles/ecs_150_project_1.dir/depend:
	cd /cygdrive/c/Users/failury/Desktop/ecs-150-project-1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/failury/Desktop/ecs-150-project-1 /cygdrive/c/Users/failury/Desktop/ecs-150-project-1 /cygdrive/c/Users/failury/Desktop/ecs-150-project-1/cmake-build-debug /cygdrive/c/Users/failury/Desktop/ecs-150-project-1/cmake-build-debug /cygdrive/c/Users/failury/Desktop/ecs-150-project-1/cmake-build-debug/CMakeFiles/ecs_150_project_1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ecs_150_project_1.dir/depend

