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
include unittest/clog/CMakeFiles/test_ob_log_file_trailer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include unittest/clog/CMakeFiles/test_ob_log_file_trailer.dir/compiler_depend.make

# Include the progress variables for this target.
include unittest/clog/CMakeFiles/test_ob_log_file_trailer.dir/progress.make

# Include the compile flags for this target's objects.
include unittest/clog/CMakeFiles/test_ob_log_file_trailer.dir/flags.make

unittest/clog/CMakeFiles/test_ob_log_file_trailer.dir/test_ob_log_file_trailer.cpp.o: unittest/clog/CMakeFiles/test_ob_log_file_trailer.dir/flags.make
unittest/clog/CMakeFiles/test_ob_log_file_trailer.dir/test_ob_log_file_trailer.cpp.o: unittest/clog/test_ob_log_file_trailer.cpp
unittest/clog/CMakeFiles/test_ob_log_file_trailer.dir/test_ob_log_file_trailer.cpp.o: unittest/clog/CMakeFiles/test_ob_log_file_trailer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object unittest/clog/CMakeFiles/test_ob_log_file_trailer.dir/test_ob_log_file_trailer.cpp.o"
	cd /home/spice/workspace/oceanbase/unittest/clog && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT unittest/clog/CMakeFiles/test_ob_log_file_trailer.dir/test_ob_log_file_trailer.cpp.o -MF CMakeFiles/test_ob_log_file_trailer.dir/test_ob_log_file_trailer.cpp.o.d -o CMakeFiles/test_ob_log_file_trailer.dir/test_ob_log_file_trailer.cpp.o -c /home/spice/workspace/oceanbase/unittest/clog/test_ob_log_file_trailer.cpp

unittest/clog/CMakeFiles/test_ob_log_file_trailer.dir/test_ob_log_file_trailer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_ob_log_file_trailer.dir/test_ob_log_file_trailer.cpp.i"
	cd /home/spice/workspace/oceanbase/unittest/clog && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spice/workspace/oceanbase/unittest/clog/test_ob_log_file_trailer.cpp > CMakeFiles/test_ob_log_file_trailer.dir/test_ob_log_file_trailer.cpp.i

unittest/clog/CMakeFiles/test_ob_log_file_trailer.dir/test_ob_log_file_trailer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_ob_log_file_trailer.dir/test_ob_log_file_trailer.cpp.s"
	cd /home/spice/workspace/oceanbase/unittest/clog && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spice/workspace/oceanbase/unittest/clog/test_ob_log_file_trailer.cpp -o CMakeFiles/test_ob_log_file_trailer.dir/test_ob_log_file_trailer.cpp.s

# Object files for target test_ob_log_file_trailer
test_ob_log_file_trailer_OBJECTS = \
"CMakeFiles/test_ob_log_file_trailer.dir/test_ob_log_file_trailer.cpp.o"

# External object files for target test_ob_log_file_trailer
test_ob_log_file_trailer_EXTERNAL_OBJECTS =

unittest/clog/test_ob_log_file_trailer: unittest/clog/CMakeFiles/test_ob_log_file_trailer.dir/test_ob_log_file_trailer.cpp.o
unittest/clog/test_ob_log_file_trailer: unittest/clog/CMakeFiles/test_ob_log_file_trailer.dir/build.make
unittest/clog/test_ob_log_file_trailer: src/observer/liboceanbase.so
unittest/clog/test_ob_log_file_trailer: deps/3rd/usr/local/oceanbase/deps/devel/lib/mariadb/libmariadb.so.3
unittest/clog/test_ob_log_file_trailer: unittest/clog/CMakeFiles/test_ob_log_file_trailer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_ob_log_file_trailer"
	cd /home/spice/workspace/oceanbase/unittest/clog && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_ob_log_file_trailer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
unittest/clog/CMakeFiles/test_ob_log_file_trailer.dir/build: unittest/clog/test_ob_log_file_trailer
.PHONY : unittest/clog/CMakeFiles/test_ob_log_file_trailer.dir/build

unittest/clog/CMakeFiles/test_ob_log_file_trailer.dir/clean:
	cd /home/spice/workspace/oceanbase/unittest/clog && $(CMAKE_COMMAND) -P CMakeFiles/test_ob_log_file_trailer.dir/cmake_clean.cmake
.PHONY : unittest/clog/CMakeFiles/test_ob_log_file_trailer.dir/clean

unittest/clog/CMakeFiles/test_ob_log_file_trailer.dir/depend:
	cd /home/spice/workspace/oceanbase && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/unittest/clog /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/unittest/clog /home/spice/workspace/oceanbase/unittest/clog/CMakeFiles/test_ob_log_file_trailer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unittest/clog/CMakeFiles/test_ob_log_file_trailer.dir/depend

