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
include deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/compiler_depend.make

# Include the progress variables for this target.
include deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/progress.make

# Include the compile flags for this target's objects.
include deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/flags.make

deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx.pch: deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/flags.make
deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx.pch: deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx.cxx
deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx.pch: deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx
deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx.pch: deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx.pch"
	cd /home/spice/workspace/oceanbase/deps/oblib/unittest/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -fpch-instantiate-templates -Xclang -emit-pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx -x c++-header -MD -MT deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx.pch -MF CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx.pch.d -o CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx.pch -c /home/spice/workspace/oceanbase/deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx.cxx

deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx.i"
	cd /home/spice/workspace/oceanbase/deps/oblib/unittest/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -fpch-instantiate-templates -Xclang -emit-pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx -x c++-header -E /home/spice/workspace/oceanbase/deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx.cxx > CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx.i

deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx.s"
	cd /home/spice/workspace/oceanbase/deps/oblib/unittest/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -fpch-instantiate-templates -Xclang -emit-pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx -x c++-header -S /home/spice/workspace/oceanbase/deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx.cxx -o CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx.s

deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/alloc/test_malloc_hook.cpp.o: deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/flags.make
deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/alloc/test_malloc_hook.cpp.o: deps/oblib/unittest/lib/alloc/test_malloc_hook.cpp
deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/alloc/test_malloc_hook.cpp.o: deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx
deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/alloc/test_malloc_hook.cpp.o: deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx.pch
deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/alloc/test_malloc_hook.cpp.o: deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/alloc/test_malloc_hook.cpp.o"
	cd /home/spice/workspace/oceanbase/deps/oblib/unittest/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx -MD -MT deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/alloc/test_malloc_hook.cpp.o -MF CMakeFiles/test_malloc_hook.dir/alloc/test_malloc_hook.cpp.o.d -o CMakeFiles/test_malloc_hook.dir/alloc/test_malloc_hook.cpp.o -c /home/spice/workspace/oceanbase/deps/oblib/unittest/lib/alloc/test_malloc_hook.cpp

deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/alloc/test_malloc_hook.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_malloc_hook.dir/alloc/test_malloc_hook.cpp.i"
	cd /home/spice/workspace/oceanbase/deps/oblib/unittest/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx -E /home/spice/workspace/oceanbase/deps/oblib/unittest/lib/alloc/test_malloc_hook.cpp > CMakeFiles/test_malloc_hook.dir/alloc/test_malloc_hook.cpp.i

deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/alloc/test_malloc_hook.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_malloc_hook.dir/alloc/test_malloc_hook.cpp.s"
	cd /home/spice/workspace/oceanbase/deps/oblib/unittest/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx -S /home/spice/workspace/oceanbase/deps/oblib/unittest/lib/alloc/test_malloc_hook.cpp -o CMakeFiles/test_malloc_hook.dir/alloc/test_malloc_hook.cpp.s

# Object files for target test_malloc_hook
test_malloc_hook_OBJECTS = \
"CMakeFiles/test_malloc_hook.dir/alloc/test_malloc_hook.cpp.o"

# External object files for target test_malloc_hook
test_malloc_hook_EXTERNAL_OBJECTS =

deps/oblib/unittest/lib/test_malloc_hook: deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/cmake_pch.hxx.pch
deps/oblib/unittest/lib/test_malloc_hook: deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/alloc/test_malloc_hook.cpp.o
deps/oblib/unittest/lib/test_malloc_hook: deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/build.make
deps/oblib/unittest/lib/test_malloc_hook: deps/easy/src/libeasy.a
deps/oblib/unittest/lib/test_malloc_hook: deps/oblib/src/liboblib.a
deps/oblib/unittest/lib/test_malloc_hook: deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable test_malloc_hook"
	cd /home/spice/workspace/oceanbase/deps/oblib/unittest/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_malloc_hook.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/build: deps/oblib/unittest/lib/test_malloc_hook
.PHONY : deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/build

deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/clean:
	cd /home/spice/workspace/oceanbase/deps/oblib/unittest/lib && $(CMAKE_COMMAND) -P CMakeFiles/test_malloc_hook.dir/cmake_clean.cmake
.PHONY : deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/clean

deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/depend:
	cd /home/spice/workspace/oceanbase && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/deps/oblib/unittest/lib /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/deps/oblib/unittest/lib /home/spice/workspace/oceanbase/deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : deps/oblib/unittest/lib/CMakeFiles/test_malloc_hook.dir/depend

