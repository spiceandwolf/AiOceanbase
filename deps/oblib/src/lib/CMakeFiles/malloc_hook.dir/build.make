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
include deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/compiler_depend.make

# Include the progress variables for this target.
include deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/progress.make

# Include the compile flags for this target's objects.
include deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/flags.make

deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/cmake_pch.hxx.pch: deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/flags.make
deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/cmake_pch.hxx.pch: deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/cmake_pch.hxx.cxx
deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/cmake_pch.hxx.pch: deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/cmake_pch.hxx
deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/cmake_pch.hxx.pch: deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/cmake_pch.hxx.pch"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -fpch-instantiate-templates -Xclang -emit-pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/cmake_pch.hxx -x c++-header -MD -MT deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/cmake_pch.hxx.pch -MF CMakeFiles/malloc_hook.dir/cmake_pch.hxx.pch.d -o CMakeFiles/malloc_hook.dir/cmake_pch.hxx.pch -c /home/spice/workspace/oceanbase/deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/cmake_pch.hxx.cxx

deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/cmake_pch.hxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/malloc_hook.dir/cmake_pch.hxx.i"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -fpch-instantiate-templates -Xclang -emit-pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/cmake_pch.hxx -x c++-header -E /home/spice/workspace/oceanbase/deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/cmake_pch.hxx.cxx > CMakeFiles/malloc_hook.dir/cmake_pch.hxx.i

deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/cmake_pch.hxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/malloc_hook.dir/cmake_pch.hxx.s"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -fpch-instantiate-templates -Xclang -emit-pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/cmake_pch.hxx -x c++-header -S /home/spice/workspace/oceanbase/deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/cmake_pch.hxx.cxx -o CMakeFiles/malloc_hook.dir/cmake_pch.hxx.s

deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/alloc/malloc_hook.cpp.o: deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/flags.make
deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/alloc/malloc_hook.cpp.o: deps/oblib/src/lib/alloc/malloc_hook.cpp
deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/alloc/malloc_hook.cpp.o: deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/cmake_pch.hxx
deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/alloc/malloc_hook.cpp.o: deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/cmake_pch.hxx.pch
deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/alloc/malloc_hook.cpp.o: deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/alloc/malloc_hook.cpp.o"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/cmake_pch.hxx -MD -MT deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/alloc/malloc_hook.cpp.o -MF CMakeFiles/malloc_hook.dir/alloc/malloc_hook.cpp.o.d -o CMakeFiles/malloc_hook.dir/alloc/malloc_hook.cpp.o -c /home/spice/workspace/oceanbase/deps/oblib/src/lib/alloc/malloc_hook.cpp

deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/alloc/malloc_hook.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/malloc_hook.dir/alloc/malloc_hook.cpp.i"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/cmake_pch.hxx -E /home/spice/workspace/oceanbase/deps/oblib/src/lib/alloc/malloc_hook.cpp > CMakeFiles/malloc_hook.dir/alloc/malloc_hook.cpp.i

deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/alloc/malloc_hook.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/malloc_hook.dir/alloc/malloc_hook.cpp.s"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/cmake_pch.hxx -S /home/spice/workspace/oceanbase/deps/oblib/src/lib/alloc/malloc_hook.cpp -o CMakeFiles/malloc_hook.dir/alloc/malloc_hook.cpp.s

# Object files for target malloc_hook
malloc_hook_OBJECTS = \
"CMakeFiles/malloc_hook.dir/alloc/malloc_hook.cpp.o"

# External object files for target malloc_hook
malloc_hook_EXTERNAL_OBJECTS =

deps/oblib/src/lib/libmalloc_hook.a: deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/cmake_pch.hxx.pch
deps/oblib/src/lib/libmalloc_hook.a: deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/alloc/malloc_hook.cpp.o
deps/oblib/src/lib/libmalloc_hook.a: deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/build.make
deps/oblib/src/lib/libmalloc_hook.a: deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libmalloc_hook.a"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && $(CMAKE_COMMAND) -P CMakeFiles/malloc_hook.dir/cmake_clean_target.cmake
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/malloc_hook.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/build: deps/oblib/src/lib/libmalloc_hook.a
.PHONY : deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/build

deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/clean:
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && $(CMAKE_COMMAND) -P CMakeFiles/malloc_hook.dir/cmake_clean.cmake
.PHONY : deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/clean

deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/depend:
	cd /home/spice/workspace/oceanbase && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/deps/oblib/src/lib /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/deps/oblib/src/lib /home/spice/workspace/oceanbase/deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : deps/oblib/src/lib/CMakeFiles/malloc_hook.dir/depend

