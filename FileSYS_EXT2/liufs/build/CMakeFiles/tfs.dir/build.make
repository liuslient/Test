# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ubuntu/user-land-filesystem/fs/liufs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/user-land-filesystem/fs/liufs/build

# Include any dependencies generated for this target.
include CMakeFiles/tfs.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/tfs.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/tfs.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tfs.dir/flags.make

CMakeFiles/tfs.dir/src/tfs.c.o: CMakeFiles/tfs.dir/flags.make
CMakeFiles/tfs.dir/src/tfs.c.o: ../src/tfs.c
CMakeFiles/tfs.dir/src/tfs.c.o: CMakeFiles/tfs.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/user-land-filesystem/fs/liufs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/tfs.dir/src/tfs.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/tfs.dir/src/tfs.c.o -MF CMakeFiles/tfs.dir/src/tfs.c.o.d -o CMakeFiles/tfs.dir/src/tfs.c.o -c /home/ubuntu/user-land-filesystem/fs/liufs/src/tfs.c

CMakeFiles/tfs.dir/src/tfs.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tfs.dir/src/tfs.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ubuntu/user-land-filesystem/fs/liufs/src/tfs.c > CMakeFiles/tfs.dir/src/tfs.c.i

CMakeFiles/tfs.dir/src/tfs.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tfs.dir/src/tfs.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ubuntu/user-land-filesystem/fs/liufs/src/tfs.c -o CMakeFiles/tfs.dir/src/tfs.c.s

CMakeFiles/tfs.dir/src/tfs_utils.c.o: CMakeFiles/tfs.dir/flags.make
CMakeFiles/tfs.dir/src/tfs_utils.c.o: ../src/tfs_utils.c
CMakeFiles/tfs.dir/src/tfs_utils.c.o: CMakeFiles/tfs.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/user-land-filesystem/fs/liufs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/tfs.dir/src/tfs_utils.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/tfs.dir/src/tfs_utils.c.o -MF CMakeFiles/tfs.dir/src/tfs_utils.c.o.d -o CMakeFiles/tfs.dir/src/tfs_utils.c.o -c /home/ubuntu/user-land-filesystem/fs/liufs/src/tfs_utils.c

CMakeFiles/tfs.dir/src/tfs_utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tfs.dir/src/tfs_utils.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ubuntu/user-land-filesystem/fs/liufs/src/tfs_utils.c > CMakeFiles/tfs.dir/src/tfs_utils.c.i

CMakeFiles/tfs.dir/src/tfs_utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tfs.dir/src/tfs_utils.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ubuntu/user-land-filesystem/fs/liufs/src/tfs_utils.c -o CMakeFiles/tfs.dir/src/tfs_utils.c.s

# Object files for target tfs
tfs_OBJECTS = \
"CMakeFiles/tfs.dir/src/tfs.c.o" \
"CMakeFiles/tfs.dir/src/tfs_utils.c.o"

# External object files for target tfs
tfs_EXTERNAL_OBJECTS =

tfs: CMakeFiles/tfs.dir/src/tfs.c.o
tfs: CMakeFiles/tfs.dir/src/tfs_utils.c.o
tfs: CMakeFiles/tfs.dir/build.make
tfs: /usr/lib/x86_64-linux-gnu/libfuse.so
tfs: /home/ubuntu/lib/libddriver.a
tfs: CMakeFiles/tfs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/user-land-filesystem/fs/liufs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable tfs"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tfs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tfs.dir/build: tfs
.PHONY : CMakeFiles/tfs.dir/build

CMakeFiles/tfs.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tfs.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tfs.dir/clean

CMakeFiles/tfs.dir/depend:
	cd /home/ubuntu/user-land-filesystem/fs/liufs/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/user-land-filesystem/fs/liufs /home/ubuntu/user-land-filesystem/fs/liufs /home/ubuntu/user-land-filesystem/fs/liufs/build /home/ubuntu/user-land-filesystem/fs/liufs/build /home/ubuntu/user-land-filesystem/fs/liufs/build/CMakeFiles/tfs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tfs.dir/depend

