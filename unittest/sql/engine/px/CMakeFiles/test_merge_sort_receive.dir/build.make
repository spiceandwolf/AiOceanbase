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
CMAKE_COMMAND = /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/cmake

# The command to remove a file.
RM = /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/spice/workspace/oceanbase

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/spice/workspace/oceanbase

# Include any dependencies generated for this target.
include unittest/sql/engine/px/CMakeFiles/test_merge_sort_receive.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include unittest/sql/engine/px/CMakeFiles/test_merge_sort_receive.dir/compiler_depend.make

# Include the progress variables for this target.
include unittest/sql/engine/px/CMakeFiles/test_merge_sort_receive.dir/progress.make

# Include the compile flags for this target's objects.
include unittest/sql/engine/px/CMakeFiles/test_merge_sort_receive.dir/flags.make

unittest/sql/engine/px/CMakeFiles/test_merge_sort_receive.dir/test_merge_sort_receive.cpp.o: unittest/sql/engine/px/CMakeFiles/test_merge_sort_receive.dir/flags.make
unittest/sql/engine/px/CMakeFiles/test_merge_sort_receive.dir/test_merge_sort_receive.cpp.o: unittest/sql/engine/px/test_merge_sort_receive.cpp
unittest/sql/engine/px/CMakeFiles/test_merge_sort_receive.dir/test_merge_sort_receive.cpp.o: unittest/sql/engine/px/CMakeFiles/test_merge_sort_receive.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object unittest/sql/engine/px/CMakeFiles/test_merge_sort_receive.dir/test_merge_sort_receive.cpp.o"
	cd /home/spice/workspace/oceanbase/unittest/sql/engine/px && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT unittest/sql/engine/px/CMakeFiles/test_merge_sort_receive.dir/test_merge_sort_receive.cpp.o -MF CMakeFiles/test_merge_sort_receive.dir/test_merge_sort_receive.cpp.o.d -o CMakeFiles/test_merge_sort_receive.dir/test_merge_sort_receive.cpp.o -c /home/spice/workspace/oceanbase/unittest/sql/engine/px/test_merge_sort_receive.cpp

unittest/sql/engine/px/CMakeFiles/test_merge_sort_receive.dir/test_merge_sort_receive.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_merge_sort_receive.dir/test_merge_sort_receive.cpp.i"
	cd /home/spice/workspace/oceanbase/unittest/sql/engine/px && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spice/workspace/oceanbase/unittest/sql/engine/px/test_merge_sort_receive.cpp > CMakeFiles/test_merge_sort_receive.dir/test_merge_sort_receive.cpp.i

unittest/sql/engine/px/CMakeFiles/test_merge_sort_receive.dir/test_merge_sort_receive.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_merge_sort_receive.dir/test_merge_sort_receive.cpp.s"
	cd /home/spice/workspace/oceanbase/unittest/sql/engine/px && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spice/workspace/oceanbase/unittest/sql/engine/px/test_merge_sort_receive.cpp -o CMakeFiles/test_merge_sort_receive.dir/test_merge_sort_receive.cpp.s

# Object files for target test_merge_sort_receive
test_merge_sort_receive_OBJECTS = \
"CMakeFiles/test_merge_sort_receive.dir/test_merge_sort_receive.cpp.o"

# External object files for target test_merge_sort_receive
test_merge_sort_receive_EXTERNAL_OBJECTS =

unittest/sql/engine/px/test_merge_sort_receive: unittest/sql/engine/px/CMakeFiles/test_merge_sort_receive.dir/test_merge_sort_receive.cpp.o
unittest/sql/engine/px/test_merge_sort_receive: unittest/sql/engine/px/CMakeFiles/test_merge_sort_receive.dir/build.make
unittest/sql/engine/px/test_merge_sort_receive: src/observer/liboceanbase.so
unittest/sql/engine/px/test_merge_sort_receive: deps/3rd/usr/local/oceanbase/deps/devel/lib/mariadb/libmariadb.so.3
unittest/sql/engine/px/test_merge_sort_receive: unittest/sql/engine/px/CMakeFiles/test_merge_sort_receive.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_merge_sort_receive"
	cd /home/spice/workspace/oceanbase/unittest/sql/engine/px && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_merge_sort_receive.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
unittest/sql/engine/px/CMakeFiles/test_merge_sort_receive.dir/build: unittest/sql/engine/px/test_merge_sort_receive
.PHONY : unittest/sql/engine/px/CMakeFiles/test_merge_sort_receive.dir/build

unittest/sql/engine/px/CMakeFiles/test_merge_sort_receive.dir/clean:
	cd /home/spice/workspace/oceanbase/unittest/sql/engine/px && $(CMAKE_COMMAND) -P CMakeFiles/test_merge_sort_receive.dir/cmake_clean.cmake
.PHONY : unittest/sql/engine/px/CMakeFiles/test_merge_sort_receive.dir/clean

unittest/sql/engine/px/CMakeFiles/test_merge_sort_receive.dir/depend:
	cd /home/spice/workspace/oceanbase && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/unittest/sql/engine/px /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/unittest/sql/engine/px /home/spice/workspace/oceanbase/unittest/sql/engine/px/CMakeFiles/test_merge_sort_receive.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unittest/sql/engine/px/CMakeFiles/test_merge_sort_receive.dir/depend

