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
include unittest/sql/code_generator/CMakeFiles/test_static_engine_cg.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include unittest/sql/code_generator/CMakeFiles/test_static_engine_cg.dir/compiler_depend.make

# Include the progress variables for this target.
include unittest/sql/code_generator/CMakeFiles/test_static_engine_cg.dir/progress.make

# Include the compile flags for this target's objects.
include unittest/sql/code_generator/CMakeFiles/test_static_engine_cg.dir/flags.make

unittest/sql/code_generator/CMakeFiles/test_static_engine_cg.dir/test_static_engine_cg.cpp.o: unittest/sql/code_generator/CMakeFiles/test_static_engine_cg.dir/flags.make
unittest/sql/code_generator/CMakeFiles/test_static_engine_cg.dir/test_static_engine_cg.cpp.o: unittest/sql/code_generator/test_static_engine_cg.cpp
unittest/sql/code_generator/CMakeFiles/test_static_engine_cg.dir/test_static_engine_cg.cpp.o: unittest/sql/code_generator/CMakeFiles/test_static_engine_cg.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object unittest/sql/code_generator/CMakeFiles/test_static_engine_cg.dir/test_static_engine_cg.cpp.o"
	cd /home/spice/workspace/oceanbase/unittest/sql/code_generator && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT unittest/sql/code_generator/CMakeFiles/test_static_engine_cg.dir/test_static_engine_cg.cpp.o -MF CMakeFiles/test_static_engine_cg.dir/test_static_engine_cg.cpp.o.d -o CMakeFiles/test_static_engine_cg.dir/test_static_engine_cg.cpp.o -c /home/spice/workspace/oceanbase/unittest/sql/code_generator/test_static_engine_cg.cpp

unittest/sql/code_generator/CMakeFiles/test_static_engine_cg.dir/test_static_engine_cg.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_static_engine_cg.dir/test_static_engine_cg.cpp.i"
	cd /home/spice/workspace/oceanbase/unittest/sql/code_generator && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spice/workspace/oceanbase/unittest/sql/code_generator/test_static_engine_cg.cpp > CMakeFiles/test_static_engine_cg.dir/test_static_engine_cg.cpp.i

unittest/sql/code_generator/CMakeFiles/test_static_engine_cg.dir/test_static_engine_cg.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_static_engine_cg.dir/test_static_engine_cg.cpp.s"
	cd /home/spice/workspace/oceanbase/unittest/sql/code_generator && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spice/workspace/oceanbase/unittest/sql/code_generator/test_static_engine_cg.cpp -o CMakeFiles/test_static_engine_cg.dir/test_static_engine_cg.cpp.s

# Object files for target test_static_engine_cg
test_static_engine_cg_OBJECTS = \
"CMakeFiles/test_static_engine_cg.dir/test_static_engine_cg.cpp.o"

# External object files for target test_static_engine_cg
test_static_engine_cg_EXTERNAL_OBJECTS = \
"/home/spice/workspace/oceanbase/unittest/sql/CMakeFiles/sql_ut_base.dir/test_sql_utils.cpp.o" \
"/home/spice/workspace/oceanbase/unittest/sql/CMakeFiles/sql_ut_base.dir/ob_mock_partition_location_cache.cpp.o" \
"/home/spice/workspace/oceanbase/unittest/sql/CMakeFiles/sql_ut_base.dir/optimizer/test_optimizer_utils.cpp.o"

unittest/sql/code_generator/test_static_engine_cg: unittest/sql/code_generator/CMakeFiles/test_static_engine_cg.dir/test_static_engine_cg.cpp.o
unittest/sql/code_generator/test_static_engine_cg: unittest/sql/CMakeFiles/sql_ut_base.dir/test_sql_utils.cpp.o
unittest/sql/code_generator/test_static_engine_cg: unittest/sql/CMakeFiles/sql_ut_base.dir/ob_mock_partition_location_cache.cpp.o
unittest/sql/code_generator/test_static_engine_cg: unittest/sql/CMakeFiles/sql_ut_base.dir/optimizer/test_optimizer_utils.cpp.o
unittest/sql/code_generator/test_static_engine_cg: unittest/sql/code_generator/CMakeFiles/test_static_engine_cg.dir/build.make
unittest/sql/code_generator/test_static_engine_cg: deps/3rd/usr/local/oceanbase/deps/devel/lib/mariadb/libmariadb.so.3
unittest/sql/code_generator/test_static_engine_cg: src/observer/liboceanbase.so
unittest/sql/code_generator/test_static_engine_cg: unittest/sql/code_generator/CMakeFiles/test_static_engine_cg.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_static_engine_cg"
	cd /home/spice/workspace/oceanbase/unittest/sql/code_generator && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_static_engine_cg.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
unittest/sql/code_generator/CMakeFiles/test_static_engine_cg.dir/build: unittest/sql/code_generator/test_static_engine_cg
.PHONY : unittest/sql/code_generator/CMakeFiles/test_static_engine_cg.dir/build

unittest/sql/code_generator/CMakeFiles/test_static_engine_cg.dir/clean:
	cd /home/spice/workspace/oceanbase/unittest/sql/code_generator && $(CMAKE_COMMAND) -P CMakeFiles/test_static_engine_cg.dir/cmake_clean.cmake
.PHONY : unittest/sql/code_generator/CMakeFiles/test_static_engine_cg.dir/clean

unittest/sql/code_generator/CMakeFiles/test_static_engine_cg.dir/depend:
	cd /home/spice/workspace/oceanbase && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/unittest/sql/code_generator /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/unittest/sql/code_generator /home/spice/workspace/oceanbase/unittest/sql/code_generator/CMakeFiles/test_static_engine_cg.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unittest/sql/code_generator/CMakeFiles/test_static_engine_cg.dir/depend

