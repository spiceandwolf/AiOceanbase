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
include unittest/clog/CMakeFiles/test_log_common.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include unittest/clog/CMakeFiles/test_log_common.dir/compiler_depend.make

# Include the progress variables for this target.
include unittest/clog/CMakeFiles/test_log_common.dir/progress.make

# Include the compile flags for this target's objects.
include unittest/clog/CMakeFiles/test_log_common.dir/flags.make

unittest/clog/CMakeFiles/test_log_common.dir/test_log_common.cpp.o: unittest/clog/CMakeFiles/test_log_common.dir/flags.make
unittest/clog/CMakeFiles/test_log_common.dir/test_log_common.cpp.o: unittest/clog/test_log_common.cpp
unittest/clog/CMakeFiles/test_log_common.dir/test_log_common.cpp.o: unittest/clog/CMakeFiles/test_log_common.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object unittest/clog/CMakeFiles/test_log_common.dir/test_log_common.cpp.o"
	cd /home/spice/workspace/oceanbase/unittest/clog && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT unittest/clog/CMakeFiles/test_log_common.dir/test_log_common.cpp.o -MF CMakeFiles/test_log_common.dir/test_log_common.cpp.o.d -o CMakeFiles/test_log_common.dir/test_log_common.cpp.o -c /home/spice/workspace/oceanbase/unittest/clog/test_log_common.cpp

unittest/clog/CMakeFiles/test_log_common.dir/test_log_common.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_log_common.dir/test_log_common.cpp.i"
	cd /home/spice/workspace/oceanbase/unittest/clog && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spice/workspace/oceanbase/unittest/clog/test_log_common.cpp > CMakeFiles/test_log_common.dir/test_log_common.cpp.i

unittest/clog/CMakeFiles/test_log_common.dir/test_log_common.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_log_common.dir/test_log_common.cpp.s"
	cd /home/spice/workspace/oceanbase/unittest/clog && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spice/workspace/oceanbase/unittest/clog/test_log_common.cpp -o CMakeFiles/test_log_common.dir/test_log_common.cpp.s

# Object files for target test_log_common
test_log_common_OBJECTS = \
"CMakeFiles/test_log_common.dir/test_log_common.cpp.o"

# External object files for target test_log_common
test_log_common_EXTERNAL_OBJECTS =

unittest/clog/test_log_common: unittest/clog/CMakeFiles/test_log_common.dir/test_log_common.cpp.o
unittest/clog/test_log_common: unittest/clog/CMakeFiles/test_log_common.dir/build.make
unittest/clog/test_log_common: src/observer/liboceanbase.so
unittest/clog/test_log_common: deps/3rd/usr/local/oceanbase/deps/devel/lib/mariadb/libmariadb.so.3
unittest/clog/test_log_common: unittest/clog/CMakeFiles/test_log_common.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_log_common"
	cd /home/spice/workspace/oceanbase/unittest/clog && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_log_common.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
unittest/clog/CMakeFiles/test_log_common.dir/build: unittest/clog/test_log_common
.PHONY : unittest/clog/CMakeFiles/test_log_common.dir/build

unittest/clog/CMakeFiles/test_log_common.dir/clean:
	cd /home/spice/workspace/oceanbase/unittest/clog && $(CMAKE_COMMAND) -P CMakeFiles/test_log_common.dir/cmake_clean.cmake
.PHONY : unittest/clog/CMakeFiles/test_log_common.dir/clean

unittest/clog/CMakeFiles/test_log_common.dir/depend:
	cd /home/spice/workspace/oceanbase && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/unittest/clog /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/unittest/clog /home/spice/workspace/oceanbase/unittest/clog/CMakeFiles/test_log_common.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unittest/clog/CMakeFiles/test_log_common.dir/depend

