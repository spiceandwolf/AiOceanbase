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
include unittest/sql/engine/expr/CMakeFiles/bit_type_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include unittest/sql/engine/expr/CMakeFiles/bit_type_test.dir/compiler_depend.make

# Include the progress variables for this target.
include unittest/sql/engine/expr/CMakeFiles/bit_type_test.dir/progress.make

# Include the compile flags for this target's objects.
include unittest/sql/engine/expr/CMakeFiles/bit_type_test.dir/flags.make

unittest/sql/engine/expr/CMakeFiles/bit_type_test.dir/bit_type_test.cpp.o: unittest/sql/engine/expr/CMakeFiles/bit_type_test.dir/flags.make
unittest/sql/engine/expr/CMakeFiles/bit_type_test.dir/bit_type_test.cpp.o: unittest/sql/engine/expr/bit_type_test.cpp
unittest/sql/engine/expr/CMakeFiles/bit_type_test.dir/bit_type_test.cpp.o: unittest/sql/engine/expr/CMakeFiles/bit_type_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object unittest/sql/engine/expr/CMakeFiles/bit_type_test.dir/bit_type_test.cpp.o"
	cd /home/spice/workspace/oceanbase/unittest/sql/engine/expr && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT unittest/sql/engine/expr/CMakeFiles/bit_type_test.dir/bit_type_test.cpp.o -MF CMakeFiles/bit_type_test.dir/bit_type_test.cpp.o.d -o CMakeFiles/bit_type_test.dir/bit_type_test.cpp.o -c /home/spice/workspace/oceanbase/unittest/sql/engine/expr/bit_type_test.cpp

unittest/sql/engine/expr/CMakeFiles/bit_type_test.dir/bit_type_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bit_type_test.dir/bit_type_test.cpp.i"
	cd /home/spice/workspace/oceanbase/unittest/sql/engine/expr && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spice/workspace/oceanbase/unittest/sql/engine/expr/bit_type_test.cpp > CMakeFiles/bit_type_test.dir/bit_type_test.cpp.i

unittest/sql/engine/expr/CMakeFiles/bit_type_test.dir/bit_type_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bit_type_test.dir/bit_type_test.cpp.s"
	cd /home/spice/workspace/oceanbase/unittest/sql/engine/expr && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spice/workspace/oceanbase/unittest/sql/engine/expr/bit_type_test.cpp -o CMakeFiles/bit_type_test.dir/bit_type_test.cpp.s

# Object files for target bit_type_test
bit_type_test_OBJECTS = \
"CMakeFiles/bit_type_test.dir/bit_type_test.cpp.o"

# External object files for target bit_type_test
bit_type_test_EXTERNAL_OBJECTS = \
"/home/spice/workspace/oceanbase/unittest/sql/CMakeFiles/sql_ut_base.dir/test_sql_utils.cpp.o" \
"/home/spice/workspace/oceanbase/unittest/sql/CMakeFiles/sql_ut_base.dir/ob_mock_partition_location_cache.cpp.o" \
"/home/spice/workspace/oceanbase/unittest/sql/CMakeFiles/sql_ut_base.dir/optimizer/test_optimizer_utils.cpp.o"

unittest/sql/engine/expr/bit_type_test: unittest/sql/engine/expr/CMakeFiles/bit_type_test.dir/bit_type_test.cpp.o
unittest/sql/engine/expr/bit_type_test: unittest/sql/CMakeFiles/sql_ut_base.dir/test_sql_utils.cpp.o
unittest/sql/engine/expr/bit_type_test: unittest/sql/CMakeFiles/sql_ut_base.dir/ob_mock_partition_location_cache.cpp.o
unittest/sql/engine/expr/bit_type_test: unittest/sql/CMakeFiles/sql_ut_base.dir/optimizer/test_optimizer_utils.cpp.o
unittest/sql/engine/expr/bit_type_test: unittest/sql/engine/expr/CMakeFiles/bit_type_test.dir/build.make
unittest/sql/engine/expr/bit_type_test: deps/3rd/usr/local/oceanbase/deps/devel/lib/mariadb/libmariadb.so.3
unittest/sql/engine/expr/bit_type_test: src/observer/liboceanbase.so
unittest/sql/engine/expr/bit_type_test: unittest/sql/engine/expr/CMakeFiles/bit_type_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bit_type_test"
	cd /home/spice/workspace/oceanbase/unittest/sql/engine/expr && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bit_type_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
unittest/sql/engine/expr/CMakeFiles/bit_type_test.dir/build: unittest/sql/engine/expr/bit_type_test
.PHONY : unittest/sql/engine/expr/CMakeFiles/bit_type_test.dir/build

unittest/sql/engine/expr/CMakeFiles/bit_type_test.dir/clean:
	cd /home/spice/workspace/oceanbase/unittest/sql/engine/expr && $(CMAKE_COMMAND) -P CMakeFiles/bit_type_test.dir/cmake_clean.cmake
.PHONY : unittest/sql/engine/expr/CMakeFiles/bit_type_test.dir/clean

unittest/sql/engine/expr/CMakeFiles/bit_type_test.dir/depend:
	cd /home/spice/workspace/oceanbase && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/unittest/sql/engine/expr /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/unittest/sql/engine/expr /home/spice/workspace/oceanbase/unittest/sql/engine/expr/CMakeFiles/bit_type_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unittest/sql/engine/expr/CMakeFiles/bit_type_test.dir/depend

