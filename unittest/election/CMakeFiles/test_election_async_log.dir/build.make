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
include unittest/election/CMakeFiles/test_election_async_log.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include unittest/election/CMakeFiles/test_election_async_log.dir/compiler_depend.make

# Include the progress variables for this target.
include unittest/election/CMakeFiles/test_election_async_log.dir/progress.make

# Include the compile flags for this target's objects.
include unittest/election/CMakeFiles/test_election_async_log.dir/flags.make

unittest/election/CMakeFiles/test_election_async_log.dir/test_election_async_log.cpp.o: unittest/election/CMakeFiles/test_election_async_log.dir/flags.make
unittest/election/CMakeFiles/test_election_async_log.dir/test_election_async_log.cpp.o: unittest/election/test_election_async_log.cpp
unittest/election/CMakeFiles/test_election_async_log.dir/test_election_async_log.cpp.o: unittest/election/CMakeFiles/test_election_async_log.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object unittest/election/CMakeFiles/test_election_async_log.dir/test_election_async_log.cpp.o"
	cd /home/spice/workspace/oceanbase/unittest/election && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT unittest/election/CMakeFiles/test_election_async_log.dir/test_election_async_log.cpp.o -MF CMakeFiles/test_election_async_log.dir/test_election_async_log.cpp.o.d -o CMakeFiles/test_election_async_log.dir/test_election_async_log.cpp.o -c /home/spice/workspace/oceanbase/unittest/election/test_election_async_log.cpp

unittest/election/CMakeFiles/test_election_async_log.dir/test_election_async_log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_election_async_log.dir/test_election_async_log.cpp.i"
	cd /home/spice/workspace/oceanbase/unittest/election && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spice/workspace/oceanbase/unittest/election/test_election_async_log.cpp > CMakeFiles/test_election_async_log.dir/test_election_async_log.cpp.i

unittest/election/CMakeFiles/test_election_async_log.dir/test_election_async_log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_election_async_log.dir/test_election_async_log.cpp.s"
	cd /home/spice/workspace/oceanbase/unittest/election && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spice/workspace/oceanbase/unittest/election/test_election_async_log.cpp -o CMakeFiles/test_election_async_log.dir/test_election_async_log.cpp.s

# Object files for target test_election_async_log
test_election_async_log_OBJECTS = \
"CMakeFiles/test_election_async_log.dir/test_election_async_log.cpp.o"

# External object files for target test_election_async_log
test_election_async_log_EXTERNAL_OBJECTS =

unittest/election/test_election_async_log: unittest/election/CMakeFiles/test_election_async_log.dir/test_election_async_log.cpp.o
unittest/election/test_election_async_log: unittest/election/CMakeFiles/test_election_async_log.dir/build.make
unittest/election/test_election_async_log: src/observer/liboceanbase.so
unittest/election/test_election_async_log: deps/3rd/usr/local/oceanbase/deps/devel/lib/mariadb/libmariadb.so.3
unittest/election/test_election_async_log: unittest/election/CMakeFiles/test_election_async_log.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_election_async_log"
	cd /home/spice/workspace/oceanbase/unittest/election && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_election_async_log.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
unittest/election/CMakeFiles/test_election_async_log.dir/build: unittest/election/test_election_async_log
.PHONY : unittest/election/CMakeFiles/test_election_async_log.dir/build

unittest/election/CMakeFiles/test_election_async_log.dir/clean:
	cd /home/spice/workspace/oceanbase/unittest/election && $(CMAKE_COMMAND) -P CMakeFiles/test_election_async_log.dir/cmake_clean.cmake
.PHONY : unittest/election/CMakeFiles/test_election_async_log.dir/clean

unittest/election/CMakeFiles/test_election_async_log.dir/depend:
	cd /home/spice/workspace/oceanbase && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/unittest/election /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/unittest/election /home/spice/workspace/oceanbase/unittest/election/CMakeFiles/test_election_async_log.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unittest/election/CMakeFiles/test_election_async_log.dir/depend

