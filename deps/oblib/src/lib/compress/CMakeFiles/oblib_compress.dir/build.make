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
include deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/compiler_depend.make

# Include the progress variables for this target.
include deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/progress.make

# Include the compile flags for this target's objects.
include deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/flags.make

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_compressor.cpp.o: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/flags.make
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_compressor.cpp.o: deps/oblib/src/lib/compress/ob_compressor.cpp
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_compressor.cpp.o: deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_compressor.cpp.o: deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_compressor.cpp.o: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_compressor.cpp.o"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -MD -MT deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_compressor.cpp.o -MF CMakeFiles/oblib_compress.dir/ob_compressor.cpp.o.d -o CMakeFiles/oblib_compress.dir/ob_compressor.cpp.o -c /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/ob_compressor.cpp

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_compressor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/oblib_compress.dir/ob_compressor.cpp.i"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -E /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/ob_compressor.cpp > CMakeFiles/oblib_compress.dir/ob_compressor.cpp.i

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_compressor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/oblib_compress.dir/ob_compressor.cpp.s"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -S /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/ob_compressor.cpp -o CMakeFiles/oblib_compress.dir/ob_compressor.cpp.s

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_compressor_pool.cpp.o: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/flags.make
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_compressor_pool.cpp.o: deps/oblib/src/lib/compress/ob_compressor_pool.cpp
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_compressor_pool.cpp.o: deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_compressor_pool.cpp.o: deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_compressor_pool.cpp.o: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_compressor_pool.cpp.o"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -MD -MT deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_compressor_pool.cpp.o -MF CMakeFiles/oblib_compress.dir/ob_compressor_pool.cpp.o.d -o CMakeFiles/oblib_compress.dir/ob_compressor_pool.cpp.o -c /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/ob_compressor_pool.cpp

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_compressor_pool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/oblib_compress.dir/ob_compressor_pool.cpp.i"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -E /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/ob_compressor_pool.cpp > CMakeFiles/oblib_compress.dir/ob_compressor_pool.cpp.i

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_compressor_pool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/oblib_compress.dir/ob_compressor_pool.cpp.s"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -S /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/ob_compressor_pool.cpp -o CMakeFiles/oblib_compress.dir/ob_compressor_pool.cpp.s

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_stream_compressor.cpp.o: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/flags.make
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_stream_compressor.cpp.o: deps/oblib/src/lib/compress/ob_stream_compressor.cpp
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_stream_compressor.cpp.o: deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_stream_compressor.cpp.o: deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_stream_compressor.cpp.o: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_stream_compressor.cpp.o"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -MD -MT deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_stream_compressor.cpp.o -MF CMakeFiles/oblib_compress.dir/ob_stream_compressor.cpp.o.d -o CMakeFiles/oblib_compress.dir/ob_stream_compressor.cpp.o -c /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/ob_stream_compressor.cpp

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_stream_compressor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/oblib_compress.dir/ob_stream_compressor.cpp.i"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -E /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/ob_stream_compressor.cpp > CMakeFiles/oblib_compress.dir/ob_stream_compressor.cpp.i

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_stream_compressor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/oblib_compress.dir/ob_stream_compressor.cpp.s"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -S /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/ob_stream_compressor.cpp -o CMakeFiles/oblib_compress.dir/ob_stream_compressor.cpp.s

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/none/ob_none_compressor.cpp.o: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/flags.make
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/none/ob_none_compressor.cpp.o: deps/oblib/src/lib/compress/none/ob_none_compressor.cpp
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/none/ob_none_compressor.cpp.o: deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/none/ob_none_compressor.cpp.o: deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/none/ob_none_compressor.cpp.o: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/none/ob_none_compressor.cpp.o"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -MD -MT deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/none/ob_none_compressor.cpp.o -MF CMakeFiles/oblib_compress.dir/none/ob_none_compressor.cpp.o.d -o CMakeFiles/oblib_compress.dir/none/ob_none_compressor.cpp.o -c /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/none/ob_none_compressor.cpp

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/none/ob_none_compressor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/oblib_compress.dir/none/ob_none_compressor.cpp.i"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -E /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/none/ob_none_compressor.cpp > CMakeFiles/oblib_compress.dir/none/ob_none_compressor.cpp.i

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/none/ob_none_compressor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/oblib_compress.dir/none/ob_none_compressor.cpp.s"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -S /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/none/ob_none_compressor.cpp -o CMakeFiles/oblib_compress.dir/none/ob_none_compressor.cpp.s

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/snappy/ob_snappy_compressor.cpp.o: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/flags.make
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/snappy/ob_snappy_compressor.cpp.o: deps/oblib/src/lib/compress/snappy/ob_snappy_compressor.cpp
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/snappy/ob_snappy_compressor.cpp.o: deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/snappy/ob_snappy_compressor.cpp.o: deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/snappy/ob_snappy_compressor.cpp.o: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/snappy/ob_snappy_compressor.cpp.o"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -MD -MT deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/snappy/ob_snappy_compressor.cpp.o -MF CMakeFiles/oblib_compress.dir/snappy/ob_snappy_compressor.cpp.o.d -o CMakeFiles/oblib_compress.dir/snappy/ob_snappy_compressor.cpp.o -c /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/snappy/ob_snappy_compressor.cpp

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/snappy/ob_snappy_compressor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/oblib_compress.dir/snappy/ob_snappy_compressor.cpp.i"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -E /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/snappy/ob_snappy_compressor.cpp > CMakeFiles/oblib_compress.dir/snappy/ob_snappy_compressor.cpp.i

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/snappy/ob_snappy_compressor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/oblib_compress.dir/snappy/ob_snappy_compressor.cpp.s"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -S /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/snappy/ob_snappy_compressor.cpp -o CMakeFiles/oblib_compress.dir/snappy/ob_snappy_compressor.cpp.s

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zlib/ob_zlib_compressor.cpp.o: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/flags.make
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zlib/ob_zlib_compressor.cpp.o: deps/oblib/src/lib/compress/zlib/ob_zlib_compressor.cpp
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zlib/ob_zlib_compressor.cpp.o: deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zlib/ob_zlib_compressor.cpp.o: deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zlib/ob_zlib_compressor.cpp.o: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zlib/ob_zlib_compressor.cpp.o"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -MD -MT deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zlib/ob_zlib_compressor.cpp.o -MF CMakeFiles/oblib_compress.dir/zlib/ob_zlib_compressor.cpp.o.d -o CMakeFiles/oblib_compress.dir/zlib/ob_zlib_compressor.cpp.o -c /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zlib/ob_zlib_compressor.cpp

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zlib/ob_zlib_compressor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/oblib_compress.dir/zlib/ob_zlib_compressor.cpp.i"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -E /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zlib/ob_zlib_compressor.cpp > CMakeFiles/oblib_compress.dir/zlib/ob_zlib_compressor.cpp.i

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zlib/ob_zlib_compressor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/oblib_compress.dir/zlib/ob_zlib_compressor.cpp.s"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -S /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zlib/ob_zlib_compressor.cpp -o CMakeFiles/oblib_compress.dir/zlib/ob_zlib_compressor.cpp.s

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd/ob_zstd_compressor.cpp.o: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/flags.make
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd/ob_zstd_compressor.cpp.o: deps/oblib/src/lib/compress/zstd/ob_zstd_compressor.cpp
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd/ob_zstd_compressor.cpp.o: deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd/ob_zstd_compressor.cpp.o: deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd/ob_zstd_compressor.cpp.o: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd/ob_zstd_compressor.cpp.o"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -MD -MT deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd/ob_zstd_compressor.cpp.o -MF CMakeFiles/oblib_compress.dir/zstd/ob_zstd_compressor.cpp.o.d -o CMakeFiles/oblib_compress.dir/zstd/ob_zstd_compressor.cpp.o -c /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd/ob_zstd_compressor.cpp

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd/ob_zstd_compressor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/oblib_compress.dir/zstd/ob_zstd_compressor.cpp.i"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -E /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd/ob_zstd_compressor.cpp > CMakeFiles/oblib_compress.dir/zstd/ob_zstd_compressor.cpp.i

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd/ob_zstd_compressor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/oblib_compress.dir/zstd/ob_zstd_compressor.cpp.s"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -S /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd/ob_zstd_compressor.cpp -o CMakeFiles/oblib_compress.dir/zstd/ob_zstd_compressor.cpp.s

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd/ob_zstd_stream_compressor.cpp.o: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/flags.make
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd/ob_zstd_stream_compressor.cpp.o: deps/oblib/src/lib/compress/zstd/ob_zstd_stream_compressor.cpp
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd/ob_zstd_stream_compressor.cpp.o: deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd/ob_zstd_stream_compressor.cpp.o: deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd/ob_zstd_stream_compressor.cpp.o: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd/ob_zstd_stream_compressor.cpp.o"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -MD -MT deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd/ob_zstd_stream_compressor.cpp.o -MF CMakeFiles/oblib_compress.dir/zstd/ob_zstd_stream_compressor.cpp.o.d -o CMakeFiles/oblib_compress.dir/zstd/ob_zstd_stream_compressor.cpp.o -c /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd/ob_zstd_stream_compressor.cpp

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd/ob_zstd_stream_compressor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/oblib_compress.dir/zstd/ob_zstd_stream_compressor.cpp.i"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -E /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd/ob_zstd_stream_compressor.cpp > CMakeFiles/oblib_compress.dir/zstd/ob_zstd_stream_compressor.cpp.i

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd/ob_zstd_stream_compressor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/oblib_compress.dir/zstd/ob_zstd_stream_compressor.cpp.s"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -S /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd/ob_zstd_stream_compressor.cpp -o CMakeFiles/oblib_compress.dir/zstd/ob_zstd_stream_compressor.cpp.s

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_compressor_1_3_8.cpp.o: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/flags.make
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_compressor_1_3_8.cpp.o: deps/oblib/src/lib/compress/zstd_1_3_8/ob_zstd_compressor_1_3_8.cpp
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_compressor_1_3_8.cpp.o: deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_compressor_1_3_8.cpp.o: deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_compressor_1_3_8.cpp.o: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_compressor_1_3_8.cpp.o"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -MD -MT deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_compressor_1_3_8.cpp.o -MF CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_compressor_1_3_8.cpp.o.d -o CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_compressor_1_3_8.cpp.o -c /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/ob_zstd_compressor_1_3_8.cpp

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_compressor_1_3_8.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_compressor_1_3_8.cpp.i"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -E /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/ob_zstd_compressor_1_3_8.cpp > CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_compressor_1_3_8.cpp.i

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_compressor_1_3_8.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_compressor_1_3_8.cpp.s"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -S /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/ob_zstd_compressor_1_3_8.cpp -o CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_compressor_1_3_8.cpp.s

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_stream_compressor_1_3_8.cpp.o: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/flags.make
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_stream_compressor_1_3_8.cpp.o: deps/oblib/src/lib/compress/zstd_1_3_8/ob_zstd_stream_compressor_1_3_8.cpp
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_stream_compressor_1_3_8.cpp.o: deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_stream_compressor_1_3_8.cpp.o: deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_stream_compressor_1_3_8.cpp.o: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_stream_compressor_1_3_8.cpp.o"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -MD -MT deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_stream_compressor_1_3_8.cpp.o -MF CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_stream_compressor_1_3_8.cpp.o.d -o CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_stream_compressor_1_3_8.cpp.o -c /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/ob_zstd_stream_compressor_1_3_8.cpp

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_stream_compressor_1_3_8.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_stream_compressor_1_3_8.cpp.i"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -E /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/ob_zstd_stream_compressor_1_3_8.cpp > CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_stream_compressor_1_3_8.cpp.i

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_stream_compressor_1_3_8.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_stream_compressor_1_3_8.cpp.s"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/deps/oblib/src/CMakeFiles/lib_pch.dir/cmake_pch.hxx -S /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/ob_zstd_stream_compressor_1_3_8.cpp -o CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_stream_compressor_1_3_8.cpp.s

oblib_compress: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_compressor.cpp.o
oblib_compress: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_compressor_pool.cpp.o
oblib_compress: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/ob_stream_compressor.cpp.o
oblib_compress: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/none/ob_none_compressor.cpp.o
oblib_compress: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/snappy/ob_snappy_compressor.cpp.o
oblib_compress: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zlib/ob_zlib_compressor.cpp.o
oblib_compress: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd/ob_zstd_compressor.cpp.o
oblib_compress: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd/ob_zstd_stream_compressor.cpp.o
oblib_compress: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_compressor_1_3_8.cpp.o
oblib_compress: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/zstd_1_3_8/ob_zstd_stream_compressor_1_3_8.cpp.o
oblib_compress: deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/build.make
.PHONY : oblib_compress

# Rule to build all files generated by this target.
deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/build: oblib_compress
.PHONY : deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/build

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/clean:
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress && $(CMAKE_COMMAND) -P CMakeFiles/oblib_compress.dir/cmake_clean.cmake
.PHONY : deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/clean

deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/depend:
	cd /home/spice/workspace/oceanbase && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : deps/oblib/src/lib/compress/CMakeFiles/oblib_compress.dir/depend
