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
include deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/oblib_compress_zstd_1_3_8.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/oblib_compress_zstd_1_3_8.dir/compiler_depend.make

# Include the progress variables for this target.
include deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/oblib_compress_zstd_1_3_8.dir/progress.make

# Include the compile flags for this target's objects.
include deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/oblib_compress_zstd_1_3_8.dir/flags.make

deps/oblib/src/lib/compress/zstd_1_3_8/zstd_1_3_8_objs.o:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating zstd_1_3_8_objs.o"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8 && ../../../../../3rd/usr/local/oceanbase/devtools/bin/ld.lld -r /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/zstd_1_3_8_objs.dir/debug.c.o /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/zstd_1_3_8_objs.dir/entropy_common.c.o /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/zstd_1_3_8_objs.dir/error_private.c.o /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/zstd_1_3_8_objs.dir/fse_compress.c.o /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/zstd_1_3_8_objs.dir/fse_decompress.c.o /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/zstd_1_3_8_objs.dir/hist.c.o /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/zstd_1_3_8_objs.dir/huf_compress.c.o /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/zstd_1_3_8_objs.dir/huf_decompress.c.o /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/zstd_1_3_8_objs.dir/pool.c.o /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/zstd_1_3_8_objs.dir/threading.c.o /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/zstd_1_3_8_objs.dir/xxhash.c.o /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/zstd_1_3_8_objs.dir/zstd_common.c.o /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/zstd_1_3_8_objs.dir/zstd_compress.c.o /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/zstd_1_3_8_objs.dir/zstd_ddict.c.o /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/zstd_1_3_8_objs.dir/zstd_decompress_block.c.o /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/zstd_1_3_8_objs.dir/zstd_decompress.c.o /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/zstd_1_3_8_objs.dir/zstd_double_fast.c.o /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/zstd_1_3_8_objs.dir/zstd_fast.c.o /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/zstd_1_3_8_objs.dir/zstd_lazy.c.o /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/zstd_1_3_8_objs.dir/zstd_ldm.c.o /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/zstd_1_3_8_objs.dir/zstdmt_compress.c.o /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/zstd_1_3_8_objs.dir/zstd_opt.c.o /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/zstd_1_3_8_objs.dir/ob_zstd_wrapper.cpp.o -o zstd_1_3_8_objs.tmp.o
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8 && ../../../../../3rd/usr/local/oceanbase/devtools/bin/llvm-objcopy --localize-hidden zstd_1_3_8_objs.tmp.o zstd_1_3_8_objs.o

oblib_compress_zstd_1_3_8: deps/oblib/src/lib/compress/zstd_1_3_8/zstd_1_3_8_objs.o
oblib_compress_zstd_1_3_8: deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/oblib_compress_zstd_1_3_8.dir/build.make
.PHONY : oblib_compress_zstd_1_3_8

# Rule to build all files generated by this target.
deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/oblib_compress_zstd_1_3_8.dir/build: oblib_compress_zstd_1_3_8
.PHONY : deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/oblib_compress_zstd_1_3_8.dir/build

deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/oblib_compress_zstd_1_3_8.dir/clean:
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8 && $(CMAKE_COMMAND) -P CMakeFiles/oblib_compress_zstd_1_3_8.dir/cmake_clean.cmake
.PHONY : deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/oblib_compress_zstd_1_3_8.dir/clean

deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/oblib_compress_zstd_1_3_8.dir/depend: deps/oblib/src/lib/compress/zstd_1_3_8/zstd_1_3_8_objs.o
	cd /home/spice/workspace/oceanbase && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8 /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8 /home/spice/workspace/oceanbase/deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/oblib_compress_zstd_1_3_8.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : deps/oblib/src/lib/compress/zstd_1_3_8/CMakeFiles/oblib_compress_zstd_1_3_8.dir/depend
