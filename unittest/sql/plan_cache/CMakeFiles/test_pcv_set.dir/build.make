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
include unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/compiler_depend.make

# Include the progress variables for this target.
include unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/progress.make

# Include the compile flags for this target's objects.
include unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/flags.make

unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/test_pcv_set.cpp.o: unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/flags.make
unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/test_pcv_set.cpp.o: unittest/sql/plan_cache/test_pcv_set.cpp
unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/test_pcv_set.cpp.o: unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/test_pcv_set.cpp.o"
	cd /home/spice/workspace/oceanbase/unittest/sql/plan_cache && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/test_pcv_set.cpp.o -MF CMakeFiles/test_pcv_set.dir/test_pcv_set.cpp.o.d -o CMakeFiles/test_pcv_set.dir/test_pcv_set.cpp.o -c /home/spice/workspace/oceanbase/unittest/sql/plan_cache/test_pcv_set.cpp

unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/test_pcv_set.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_pcv_set.dir/test_pcv_set.cpp.i"
	cd /home/spice/workspace/oceanbase/unittest/sql/plan_cache && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spice/workspace/oceanbase/unittest/sql/plan_cache/test_pcv_set.cpp > CMakeFiles/test_pcv_set.dir/test_pcv_set.cpp.i

unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/test_pcv_set.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_pcv_set.dir/test_pcv_set.cpp.s"
	cd /home/spice/workspace/oceanbase/unittest/sql/plan_cache && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spice/workspace/oceanbase/unittest/sql/plan_cache/test_pcv_set.cpp -o CMakeFiles/test_pcv_set.dir/test_pcv_set.cpp.s

unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/test_sql.cpp.o: unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/flags.make
unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/test_sql.cpp.o: unittest/sql/plan_cache/test_sql.cpp
unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/test_sql.cpp.o: unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/test_sql.cpp.o"
	cd /home/spice/workspace/oceanbase/unittest/sql/plan_cache && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/test_sql.cpp.o -MF CMakeFiles/test_pcv_set.dir/test_sql.cpp.o.d -o CMakeFiles/test_pcv_set.dir/test_sql.cpp.o -c /home/spice/workspace/oceanbase/unittest/sql/plan_cache/test_sql.cpp

unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/test_sql.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_pcv_set.dir/test_sql.cpp.i"
	cd /home/spice/workspace/oceanbase/unittest/sql/plan_cache && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spice/workspace/oceanbase/unittest/sql/plan_cache/test_sql.cpp > CMakeFiles/test_pcv_set.dir/test_sql.cpp.i

unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/test_sql.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_pcv_set.dir/test_sql.cpp.s"
	cd /home/spice/workspace/oceanbase/unittest/sql/plan_cache && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spice/workspace/oceanbase/unittest/sql/plan_cache/test_sql.cpp -o CMakeFiles/test_pcv_set.dir/test_sql.cpp.s

# Object files for target test_pcv_set
test_pcv_set_OBJECTS = \
"CMakeFiles/test_pcv_set.dir/test_pcv_set.cpp.o" \
"CMakeFiles/test_pcv_set.dir/test_sql.cpp.o"

# External object files for target test_pcv_set
test_pcv_set_EXTERNAL_OBJECTS = \
"/home/spice/workspace/oceanbase/unittest/sql/CMakeFiles/sql_ut_base.dir/test_sql_utils.cpp.o" \
"/home/spice/workspace/oceanbase/unittest/sql/CMakeFiles/sql_ut_base.dir/ob_mock_partition_location_cache.cpp.o" \
"/home/spice/workspace/oceanbase/unittest/sql/CMakeFiles/sql_ut_base.dir/optimizer/test_optimizer_utils.cpp.o"

unittest/sql/plan_cache/test_pcv_set: unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/test_pcv_set.cpp.o
unittest/sql/plan_cache/test_pcv_set: unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/test_sql.cpp.o
unittest/sql/plan_cache/test_pcv_set: unittest/sql/CMakeFiles/sql_ut_base.dir/test_sql_utils.cpp.o
unittest/sql/plan_cache/test_pcv_set: unittest/sql/CMakeFiles/sql_ut_base.dir/ob_mock_partition_location_cache.cpp.o
unittest/sql/plan_cache/test_pcv_set: unittest/sql/CMakeFiles/sql_ut_base.dir/optimizer/test_optimizer_utils.cpp.o
unittest/sql/plan_cache/test_pcv_set: unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/build.make
unittest/sql/plan_cache/test_pcv_set: deps/3rd/usr/local/oceanbase/deps/devel/lib/mariadb/libmariadb.so.3
unittest/sql/plan_cache/test_pcv_set: src/observer/liboceanbase.so
unittest/sql/plan_cache/test_pcv_set: unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable test_pcv_set"
	cd /home/spice/workspace/oceanbase/unittest/sql/plan_cache && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_pcv_set.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/build: unittest/sql/plan_cache/test_pcv_set
.PHONY : unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/build

unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/clean:
	cd /home/spice/workspace/oceanbase/unittest/sql/plan_cache && $(CMAKE_COMMAND) -P CMakeFiles/test_pcv_set.dir/cmake_clean.cmake
.PHONY : unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/clean

unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/depend:
	cd /home/spice/workspace/oceanbase && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/unittest/sql/plan_cache /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/unittest/sql/plan_cache /home/spice/workspace/oceanbase/unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unittest/sql/plan_cache/CMakeFiles/test_pcv_set.dir/depend

