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
include unittest/share/CMakeFiles/test_obj_cast.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include unittest/share/CMakeFiles/test_obj_cast.dir/compiler_depend.make

# Include the progress variables for this target.
include unittest/share/CMakeFiles/test_obj_cast.dir/progress.make

# Include the compile flags for this target's objects.
include unittest/share/CMakeFiles/test_obj_cast.dir/flags.make

unittest/share/CMakeFiles/test_obj_cast.dir/test_obj_cast.cpp.o: unittest/share/CMakeFiles/test_obj_cast.dir/flags.make
unittest/share/CMakeFiles/test_obj_cast.dir/test_obj_cast.cpp.o: unittest/share/test_obj_cast.cpp
unittest/share/CMakeFiles/test_obj_cast.dir/test_obj_cast.cpp.o: unittest/share/CMakeFiles/test_obj_cast.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object unittest/share/CMakeFiles/test_obj_cast.dir/test_obj_cast.cpp.o"
	cd /home/spice/workspace/oceanbase/unittest/share && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT unittest/share/CMakeFiles/test_obj_cast.dir/test_obj_cast.cpp.o -MF CMakeFiles/test_obj_cast.dir/test_obj_cast.cpp.o.d -o CMakeFiles/test_obj_cast.dir/test_obj_cast.cpp.o -c /home/spice/workspace/oceanbase/unittest/share/test_obj_cast.cpp

unittest/share/CMakeFiles/test_obj_cast.dir/test_obj_cast.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_obj_cast.dir/test_obj_cast.cpp.i"
	cd /home/spice/workspace/oceanbase/unittest/share && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spice/workspace/oceanbase/unittest/share/test_obj_cast.cpp > CMakeFiles/test_obj_cast.dir/test_obj_cast.cpp.i

unittest/share/CMakeFiles/test_obj_cast.dir/test_obj_cast.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_obj_cast.dir/test_obj_cast.cpp.s"
	cd /home/spice/workspace/oceanbase/unittest/share && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spice/workspace/oceanbase/unittest/share/test_obj_cast.cpp -o CMakeFiles/test_obj_cast.dir/test_obj_cast.cpp.s

# Object files for target test_obj_cast
test_obj_cast_OBJECTS = \
"CMakeFiles/test_obj_cast.dir/test_obj_cast.cpp.o"

# External object files for target test_obj_cast
test_obj_cast_EXTERNAL_OBJECTS =

unittest/share/test_obj_cast: unittest/share/CMakeFiles/test_obj_cast.dir/test_obj_cast.cpp.o
unittest/share/test_obj_cast: unittest/share/CMakeFiles/test_obj_cast.dir/build.make
unittest/share/test_obj_cast: src/observer/liboceanbase.so
unittest/share/test_obj_cast: deps/3rd/usr/local/oceanbase/deps/devel/lib/mariadb/libmariadb.so.3
unittest/share/test_obj_cast: unittest/share/CMakeFiles/test_obj_cast.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_obj_cast"
	cd /home/spice/workspace/oceanbase/unittest/share && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_obj_cast.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
unittest/share/CMakeFiles/test_obj_cast.dir/build: unittest/share/test_obj_cast
.PHONY : unittest/share/CMakeFiles/test_obj_cast.dir/build

unittest/share/CMakeFiles/test_obj_cast.dir/clean:
	cd /home/spice/workspace/oceanbase/unittest/share && $(CMAKE_COMMAND) -P CMakeFiles/test_obj_cast.dir/cmake_clean.cmake
.PHONY : unittest/share/CMakeFiles/test_obj_cast.dir/clean

unittest/share/CMakeFiles/test_obj_cast.dir/depend:
	cd /home/spice/workspace/oceanbase && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/unittest/share /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/unittest/share /home/spice/workspace/oceanbase/unittest/share/CMakeFiles/test_obj_cast.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unittest/share/CMakeFiles/test_obj_cast.dir/depend

