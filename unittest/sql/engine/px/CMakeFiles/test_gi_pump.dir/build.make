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
include unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/compiler_depend.make

# Include the progress variables for this target.
include unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/progress.make

# Include the compile flags for this target's objects.
include unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/flags.make

unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/test_gi_pump.cpp.o: unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/flags.make
unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/test_gi_pump.cpp.o: unittest/sql/engine/px/test_gi_pump.cpp
unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/test_gi_pump.cpp.o: unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/test_gi_pump.cpp.o"
	cd /home/spice/workspace/oceanbase/unittest/sql/engine/px && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/test_gi_pump.cpp.o -MF CMakeFiles/test_gi_pump.dir/test_gi_pump.cpp.o.d -o CMakeFiles/test_gi_pump.dir/test_gi_pump.cpp.o -c /home/spice/workspace/oceanbase/unittest/sql/engine/px/test_gi_pump.cpp

unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/test_gi_pump.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_gi_pump.dir/test_gi_pump.cpp.i"
	cd /home/spice/workspace/oceanbase/unittest/sql/engine/px && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spice/workspace/oceanbase/unittest/sql/engine/px/test_gi_pump.cpp > CMakeFiles/test_gi_pump.dir/test_gi_pump.cpp.i

unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/test_gi_pump.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_gi_pump.dir/test_gi_pump.cpp.s"
	cd /home/spice/workspace/oceanbase/unittest/sql/engine/px && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spice/workspace/oceanbase/unittest/sql/engine/px/test_gi_pump.cpp -o CMakeFiles/test_gi_pump.dir/test_gi_pump.cpp.s

unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/ob_fake_partition_service.cpp.o: unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/flags.make
unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/ob_fake_partition_service.cpp.o: unittest/sql/engine/px/ob_fake_partition_service.cpp
unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/ob_fake_partition_service.cpp.o: unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/ob_fake_partition_service.cpp.o"
	cd /home/spice/workspace/oceanbase/unittest/sql/engine/px && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/ob_fake_partition_service.cpp.o -MF CMakeFiles/test_gi_pump.dir/ob_fake_partition_service.cpp.o.d -o CMakeFiles/test_gi_pump.dir/ob_fake_partition_service.cpp.o -c /home/spice/workspace/oceanbase/unittest/sql/engine/px/ob_fake_partition_service.cpp

unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/ob_fake_partition_service.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_gi_pump.dir/ob_fake_partition_service.cpp.i"
	cd /home/spice/workspace/oceanbase/unittest/sql/engine/px && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spice/workspace/oceanbase/unittest/sql/engine/px/ob_fake_partition_service.cpp > CMakeFiles/test_gi_pump.dir/ob_fake_partition_service.cpp.i

unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/ob_fake_partition_service.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_gi_pump.dir/ob_fake_partition_service.cpp.s"
	cd /home/spice/workspace/oceanbase/unittest/sql/engine/px && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spice/workspace/oceanbase/unittest/sql/engine/px/ob_fake_partition_service.cpp -o CMakeFiles/test_gi_pump.dir/ob_fake_partition_service.cpp.s

unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/ob_fake_partition_location_cache.cpp.o: unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/flags.make
unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/ob_fake_partition_location_cache.cpp.o: unittest/sql/engine/px/ob_fake_partition_location_cache.cpp
unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/ob_fake_partition_location_cache.cpp.o: unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/ob_fake_partition_location_cache.cpp.o"
	cd /home/spice/workspace/oceanbase/unittest/sql/engine/px && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/ob_fake_partition_location_cache.cpp.o -MF CMakeFiles/test_gi_pump.dir/ob_fake_partition_location_cache.cpp.o.d -o CMakeFiles/test_gi_pump.dir/ob_fake_partition_location_cache.cpp.o -c /home/spice/workspace/oceanbase/unittest/sql/engine/px/ob_fake_partition_location_cache.cpp

unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/ob_fake_partition_location_cache.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_gi_pump.dir/ob_fake_partition_location_cache.cpp.i"
	cd /home/spice/workspace/oceanbase/unittest/sql/engine/px && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spice/workspace/oceanbase/unittest/sql/engine/px/ob_fake_partition_location_cache.cpp > CMakeFiles/test_gi_pump.dir/ob_fake_partition_location_cache.cpp.i

unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/ob_fake_partition_location_cache.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_gi_pump.dir/ob_fake_partition_location_cache.cpp.s"
	cd /home/spice/workspace/oceanbase/unittest/sql/engine/px && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spice/workspace/oceanbase/unittest/sql/engine/px/ob_fake_partition_location_cache.cpp -o CMakeFiles/test_gi_pump.dir/ob_fake_partition_location_cache.cpp.s

# Object files for target test_gi_pump
test_gi_pump_OBJECTS = \
"CMakeFiles/test_gi_pump.dir/test_gi_pump.cpp.o" \
"CMakeFiles/test_gi_pump.dir/ob_fake_partition_service.cpp.o" \
"CMakeFiles/test_gi_pump.dir/ob_fake_partition_location_cache.cpp.o"

# External object files for target test_gi_pump
test_gi_pump_EXTERNAL_OBJECTS =

unittest/sql/engine/px/test_gi_pump: unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/test_gi_pump.cpp.o
unittest/sql/engine/px/test_gi_pump: unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/ob_fake_partition_service.cpp.o
unittest/sql/engine/px/test_gi_pump: unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/ob_fake_partition_location_cache.cpp.o
unittest/sql/engine/px/test_gi_pump: unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/build.make
unittest/sql/engine/px/test_gi_pump: src/observer/liboceanbase.so
unittest/sql/engine/px/test_gi_pump: deps/3rd/usr/local/oceanbase/deps/devel/lib/mariadb/libmariadb.so.3
unittest/sql/engine/px/test_gi_pump: unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable test_gi_pump"
	cd /home/spice/workspace/oceanbase/unittest/sql/engine/px && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_gi_pump.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/build: unittest/sql/engine/px/test_gi_pump
.PHONY : unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/build

unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/clean:
	cd /home/spice/workspace/oceanbase/unittest/sql/engine/px && $(CMAKE_COMMAND) -P CMakeFiles/test_gi_pump.dir/cmake_clean.cmake
.PHONY : unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/clean

unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/depend:
	cd /home/spice/workspace/oceanbase && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/unittest/sql/engine/px /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/unittest/sql/engine/px /home/spice/workspace/oceanbase/unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unittest/sql/engine/px/CMakeFiles/test_gi_pump.dir/depend

