# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /snap/cmake/876/bin/cmake

# The command to remove a file.
RM = /snap/cmake/876/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/peter/Documents/learning/C++/OpenGL/test_project1/glfw-3.3.4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/peter/Documents/learning/C++/OpenGL/test_project1/glfw-3.3.4/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/reopen.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/reopen.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/reopen.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/reopen.dir/flags.make

tests/CMakeFiles/reopen.dir/reopen.c.o: tests/CMakeFiles/reopen.dir/flags.make
tests/CMakeFiles/reopen.dir/reopen.c.o: ../tests/reopen.c
tests/CMakeFiles/reopen.dir/reopen.c.o: tests/CMakeFiles/reopen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/peter/Documents/learning/C++/OpenGL/test_project1/glfw-3.3.4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/reopen.dir/reopen.c.o"
	cd /home/peter/Documents/learning/C++/OpenGL/test_project1/glfw-3.3.4/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/CMakeFiles/reopen.dir/reopen.c.o -MF CMakeFiles/reopen.dir/reopen.c.o.d -o CMakeFiles/reopen.dir/reopen.c.o -c /home/peter/Documents/learning/C++/OpenGL/test_project1/glfw-3.3.4/tests/reopen.c

tests/CMakeFiles/reopen.dir/reopen.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/reopen.dir/reopen.c.i"
	cd /home/peter/Documents/learning/C++/OpenGL/test_project1/glfw-3.3.4/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/peter/Documents/learning/C++/OpenGL/test_project1/glfw-3.3.4/tests/reopen.c > CMakeFiles/reopen.dir/reopen.c.i

tests/CMakeFiles/reopen.dir/reopen.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/reopen.dir/reopen.c.s"
	cd /home/peter/Documents/learning/C++/OpenGL/test_project1/glfw-3.3.4/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/peter/Documents/learning/C++/OpenGL/test_project1/glfw-3.3.4/tests/reopen.c -o CMakeFiles/reopen.dir/reopen.c.s

tests/CMakeFiles/reopen.dir/__/deps/glad_gl.c.o: tests/CMakeFiles/reopen.dir/flags.make
tests/CMakeFiles/reopen.dir/__/deps/glad_gl.c.o: ../deps/glad_gl.c
tests/CMakeFiles/reopen.dir/__/deps/glad_gl.c.o: tests/CMakeFiles/reopen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/peter/Documents/learning/C++/OpenGL/test_project1/glfw-3.3.4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/CMakeFiles/reopen.dir/__/deps/glad_gl.c.o"
	cd /home/peter/Documents/learning/C++/OpenGL/test_project1/glfw-3.3.4/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/CMakeFiles/reopen.dir/__/deps/glad_gl.c.o -MF CMakeFiles/reopen.dir/__/deps/glad_gl.c.o.d -o CMakeFiles/reopen.dir/__/deps/glad_gl.c.o -c /home/peter/Documents/learning/C++/OpenGL/test_project1/glfw-3.3.4/deps/glad_gl.c

tests/CMakeFiles/reopen.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/reopen.dir/__/deps/glad_gl.c.i"
	cd /home/peter/Documents/learning/C++/OpenGL/test_project1/glfw-3.3.4/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/peter/Documents/learning/C++/OpenGL/test_project1/glfw-3.3.4/deps/glad_gl.c > CMakeFiles/reopen.dir/__/deps/glad_gl.c.i

tests/CMakeFiles/reopen.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/reopen.dir/__/deps/glad_gl.c.s"
	cd /home/peter/Documents/learning/C++/OpenGL/test_project1/glfw-3.3.4/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/peter/Documents/learning/C++/OpenGL/test_project1/glfw-3.3.4/deps/glad_gl.c -o CMakeFiles/reopen.dir/__/deps/glad_gl.c.s

# Object files for target reopen
reopen_OBJECTS = \
"CMakeFiles/reopen.dir/reopen.c.o" \
"CMakeFiles/reopen.dir/__/deps/glad_gl.c.o"

# External object files for target reopen
reopen_EXTERNAL_OBJECTS =

tests/reopen: tests/CMakeFiles/reopen.dir/reopen.c.o
tests/reopen: tests/CMakeFiles/reopen.dir/__/deps/glad_gl.c.o
tests/reopen: tests/CMakeFiles/reopen.dir/build.make
tests/reopen: src/libglfw3.a
tests/reopen: /usr/lib/x86_64-linux-gnu/libm.so
tests/reopen: /usr/lib/x86_64-linux-gnu/librt.so
tests/reopen: /usr/lib/x86_64-linux-gnu/libm.so
tests/reopen: /usr/lib/x86_64-linux-gnu/libX11.so
tests/reopen: tests/CMakeFiles/reopen.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/peter/Documents/learning/C++/OpenGL/test_project1/glfw-3.3.4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable reopen"
	cd /home/peter/Documents/learning/C++/OpenGL/test_project1/glfw-3.3.4/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/reopen.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/reopen.dir/build: tests/reopen
.PHONY : tests/CMakeFiles/reopen.dir/build

tests/CMakeFiles/reopen.dir/clean:
	cd /home/peter/Documents/learning/C++/OpenGL/test_project1/glfw-3.3.4/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/reopen.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/reopen.dir/clean

tests/CMakeFiles/reopen.dir/depend:
	cd /home/peter/Documents/learning/C++/OpenGL/test_project1/glfw-3.3.4/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/peter/Documents/learning/C++/OpenGL/test_project1/glfw-3.3.4 /home/peter/Documents/learning/C++/OpenGL/test_project1/glfw-3.3.4/tests /home/peter/Documents/learning/C++/OpenGL/test_project1/glfw-3.3.4/build /home/peter/Documents/learning/C++/OpenGL/test_project1/glfw-3.3.4/build/tests /home/peter/Documents/learning/C++/OpenGL/test_project1/glfw-3.3.4/build/tests/CMakeFiles/reopen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/reopen.dir/depend

