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
include deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/compiler_depend.make

# Include the progress variables for this target.
include deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/progress.make

# Include the compile flags for this target's objects.
include deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/flags.make

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_aarch64_sysv_elf_gas.S.o: deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/flags.make
deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_aarch64_sysv_elf_gas.S.o: deps/oblib/src/lib/coro/context/asm/jump_aarch64_sysv_elf_gas.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building ASM object deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_aarch64_sysv_elf_gas.S.o"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_aarch64_sysv_elf_gas.S.o -c /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/jump_aarch64_sysv_elf_gas.S

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_aarch64_sysv_elf_gas.S.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing ASM source to CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_aarch64_sysv_elf_gas.S.i"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -E /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/jump_aarch64_sysv_elf_gas.S > CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_aarch64_sysv_elf_gas.S.i

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_aarch64_sysv_elf_gas.S.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling ASM source to assembly CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_aarch64_sysv_elf_gas.S.s"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -S /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/jump_aarch64_sysv_elf_gas.S -o CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_aarch64_sysv_elf_gas.S.s

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_aarch64_sysv_elf_gas.S.o: deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/flags.make
deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_aarch64_sysv_elf_gas.S.o: deps/oblib/src/lib/coro/context/asm/make_aarch64_sysv_elf_gas.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building ASM object deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_aarch64_sysv_elf_gas.S.o"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_aarch64_sysv_elf_gas.S.o -c /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/make_aarch64_sysv_elf_gas.S

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_aarch64_sysv_elf_gas.S.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing ASM source to CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_aarch64_sysv_elf_gas.S.i"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -E /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/make_aarch64_sysv_elf_gas.S > CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_aarch64_sysv_elf_gas.S.i

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_aarch64_sysv_elf_gas.S.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling ASM source to assembly CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_aarch64_sysv_elf_gas.S.s"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -S /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/make_aarch64_sysv_elf_gas.S -o CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_aarch64_sysv_elf_gas.S.s

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_aarch64_sysv_elf_gas.S.o: deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/flags.make
deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_aarch64_sysv_elf_gas.S.o: deps/oblib/src/lib/coro/context/asm/ontop_aarch64_sysv_elf_gas.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building ASM object deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_aarch64_sysv_elf_gas.S.o"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_aarch64_sysv_elf_gas.S.o -c /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/ontop_aarch64_sysv_elf_gas.S

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_aarch64_sysv_elf_gas.S.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing ASM source to CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_aarch64_sysv_elf_gas.S.i"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -E /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/ontop_aarch64_sysv_elf_gas.S > CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_aarch64_sysv_elf_gas.S.i

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_aarch64_sysv_elf_gas.S.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling ASM source to assembly CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_aarch64_sysv_elf_gas.S.s"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -S /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/ontop_aarch64_sysv_elf_gas.S -o CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_aarch64_sysv_elf_gas.S.s

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_x86_64_sysv_elf_gas.S.o: deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/flags.make
deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_x86_64_sysv_elf_gas.S.o: deps/oblib/src/lib/coro/context/asm/jump_x86_64_sysv_elf_gas.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building ASM object deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_x86_64_sysv_elf_gas.S.o"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_x86_64_sysv_elf_gas.S.o -c /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/jump_x86_64_sysv_elf_gas.S

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_x86_64_sysv_elf_gas.S.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing ASM source to CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_x86_64_sysv_elf_gas.S.i"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -E /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/jump_x86_64_sysv_elf_gas.S > CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_x86_64_sysv_elf_gas.S.i

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_x86_64_sysv_elf_gas.S.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling ASM source to assembly CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_x86_64_sysv_elf_gas.S.s"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -S /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/jump_x86_64_sysv_elf_gas.S -o CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_x86_64_sysv_elf_gas.S.s

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_x86_64_sysv_elf_gas.S.o: deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/flags.make
deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_x86_64_sysv_elf_gas.S.o: deps/oblib/src/lib/coro/context/asm/make_x86_64_sysv_elf_gas.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building ASM object deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_x86_64_sysv_elf_gas.S.o"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_x86_64_sysv_elf_gas.S.o -c /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/make_x86_64_sysv_elf_gas.S

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_x86_64_sysv_elf_gas.S.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing ASM source to CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_x86_64_sysv_elf_gas.S.i"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -E /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/make_x86_64_sysv_elf_gas.S > CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_x86_64_sysv_elf_gas.S.i

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_x86_64_sysv_elf_gas.S.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling ASM source to assembly CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_x86_64_sysv_elf_gas.S.s"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -S /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/make_x86_64_sysv_elf_gas.S -o CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_x86_64_sysv_elf_gas.S.s

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_x86_64_sysv_elf_gas.S.o: deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/flags.make
deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_x86_64_sysv_elf_gas.S.o: deps/oblib/src/lib/coro/context/asm/ontop_x86_64_sysv_elf_gas.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building ASM object deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_x86_64_sysv_elf_gas.S.o"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_x86_64_sysv_elf_gas.S.o -c /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/ontop_x86_64_sysv_elf_gas.S

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_x86_64_sysv_elf_gas.S.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing ASM source to CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_x86_64_sysv_elf_gas.S.i"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -E /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/ontop_x86_64_sysv_elf_gas.S > CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_x86_64_sysv_elf_gas.S.i

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_x86_64_sysv_elf_gas.S.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling ASM source to assembly CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_x86_64_sysv_elf_gas.S.s"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -S /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/ontop_x86_64_sysv_elf_gas.S -o CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_x86_64_sysv_elf_gas.S.s

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_sw_64_aapcs_elf_gas.S.o: deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/flags.make
deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_sw_64_aapcs_elf_gas.S.o: deps/oblib/src/lib/coro/context/asm/make_sw_64_aapcs_elf_gas.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building ASM object deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_sw_64_aapcs_elf_gas.S.o"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_sw_64_aapcs_elf_gas.S.o -c /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/make_sw_64_aapcs_elf_gas.S

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_sw_64_aapcs_elf_gas.S.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing ASM source to CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_sw_64_aapcs_elf_gas.S.i"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -E /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/make_sw_64_aapcs_elf_gas.S > CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_sw_64_aapcs_elf_gas.S.i

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_sw_64_aapcs_elf_gas.S.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling ASM source to assembly CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_sw_64_aapcs_elf_gas.S.s"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -S /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/make_sw_64_aapcs_elf_gas.S -o CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_sw_64_aapcs_elf_gas.S.s

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_sw_64_aapcs_elf_gas.S.o: deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/flags.make
deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_sw_64_aapcs_elf_gas.S.o: deps/oblib/src/lib/coro/context/asm/jump_sw_64_aapcs_elf_gas.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building ASM object deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_sw_64_aapcs_elf_gas.S.o"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_sw_64_aapcs_elf_gas.S.o -c /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/jump_sw_64_aapcs_elf_gas.S

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_sw_64_aapcs_elf_gas.S.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing ASM source to CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_sw_64_aapcs_elf_gas.S.i"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -E /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/jump_sw_64_aapcs_elf_gas.S > CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_sw_64_aapcs_elf_gas.S.i

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_sw_64_aapcs_elf_gas.S.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling ASM source to assembly CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_sw_64_aapcs_elf_gas.S.s"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -S /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/jump_sw_64_aapcs_elf_gas.S -o CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_sw_64_aapcs_elf_gas.S.s

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_sw_64_aapcs_elf_gas.S.o: deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/flags.make
deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_sw_64_aapcs_elf_gas.S.o: deps/oblib/src/lib/coro/context/asm/ontop_sw_64_aapcs_elf_gas.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building ASM object deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_sw_64_aapcs_elf_gas.S.o"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_sw_64_aapcs_elf_gas.S.o -c /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/ontop_sw_64_aapcs_elf_gas.S

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_sw_64_aapcs_elf_gas.S.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing ASM source to CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_sw_64_aapcs_elf_gas.S.i"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -E /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/ontop_sw_64_aapcs_elf_gas.S > CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_sw_64_aapcs_elf_gas.S.i

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_sw_64_aapcs_elf_gas.S.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling ASM source to assembly CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_sw_64_aapcs_elf_gas.S.s"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -S /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/ontop_sw_64_aapcs_elf_gas.S -o CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_sw_64_aapcs_elf_gas.S.s

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_loongarch64_sysv_elf_gas.S.o: deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/flags.make
deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_loongarch64_sysv_elf_gas.S.o: deps/oblib/src/lib/coro/context/asm/jump_loongarch64_sysv_elf_gas.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building ASM object deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_loongarch64_sysv_elf_gas.S.o"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_loongarch64_sysv_elf_gas.S.o -c /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/jump_loongarch64_sysv_elf_gas.S

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_loongarch64_sysv_elf_gas.S.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing ASM source to CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_loongarch64_sysv_elf_gas.S.i"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -E /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/jump_loongarch64_sysv_elf_gas.S > CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_loongarch64_sysv_elf_gas.S.i

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_loongarch64_sysv_elf_gas.S.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling ASM source to assembly CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_loongarch64_sysv_elf_gas.S.s"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -S /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/jump_loongarch64_sysv_elf_gas.S -o CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_loongarch64_sysv_elf_gas.S.s

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_loongarch64_sysv_elf_gas.S.o: deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/flags.make
deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_loongarch64_sysv_elf_gas.S.o: deps/oblib/src/lib/coro/context/asm/make_loongarch64_sysv_elf_gas.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building ASM object deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_loongarch64_sysv_elf_gas.S.o"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_loongarch64_sysv_elf_gas.S.o -c /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/make_loongarch64_sysv_elf_gas.S

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_loongarch64_sysv_elf_gas.S.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing ASM source to CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_loongarch64_sysv_elf_gas.S.i"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -E /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/make_loongarch64_sysv_elf_gas.S > CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_loongarch64_sysv_elf_gas.S.i

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_loongarch64_sysv_elf_gas.S.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling ASM source to assembly CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_loongarch64_sysv_elf_gas.S.s"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -S /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/make_loongarch64_sysv_elf_gas.S -o CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_loongarch64_sysv_elf_gas.S.s

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_loongarch64_sysv_elf_gas.S.o: deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/flags.make
deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_loongarch64_sysv_elf_gas.S.o: deps/oblib/src/lib/coro/context/asm/ontop_loongarch64_sysv_elf_gas.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building ASM object deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_loongarch64_sysv_elf_gas.S.o"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_loongarch64_sysv_elf_gas.S.o -c /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/ontop_loongarch64_sysv_elf_gas.S

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_loongarch64_sysv_elf_gas.S.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing ASM source to CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_loongarch64_sysv_elf_gas.S.i"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -E /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/ontop_loongarch64_sysv_elf_gas.S > CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_loongarch64_sysv_elf_gas.S.i

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_loongarch64_sysv_elf_gas.S.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling ASM source to assembly CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_loongarch64_sysv_elf_gas.S.s"
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -S /home/spice/workspace/oceanbase/deps/oblib/src/lib/coro/context/asm/ontop_loongarch64_sysv_elf_gas.S -o CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_loongarch64_sysv_elf_gas.S.s

oblib_lib_coro_context: deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_aarch64_sysv_elf_gas.S.o
oblib_lib_coro_context: deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_aarch64_sysv_elf_gas.S.o
oblib_lib_coro_context: deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_aarch64_sysv_elf_gas.S.o
oblib_lib_coro_context: deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_x86_64_sysv_elf_gas.S.o
oblib_lib_coro_context: deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_x86_64_sysv_elf_gas.S.o
oblib_lib_coro_context: deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_x86_64_sysv_elf_gas.S.o
oblib_lib_coro_context: deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_sw_64_aapcs_elf_gas.S.o
oblib_lib_coro_context: deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_sw_64_aapcs_elf_gas.S.o
oblib_lib_coro_context: deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_sw_64_aapcs_elf_gas.S.o
oblib_lib_coro_context: deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/jump_loongarch64_sysv_elf_gas.S.o
oblib_lib_coro_context: deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/make_loongarch64_sysv_elf_gas.S.o
oblib_lib_coro_context: deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/coro/context/asm/ontop_loongarch64_sysv_elf_gas.S.o
oblib_lib_coro_context: deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/build.make
.PHONY : oblib_lib_coro_context

# Rule to build all files generated by this target.
deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/build: oblib_lib_coro_context
.PHONY : deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/build

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/clean:
	cd /home/spice/workspace/oceanbase/deps/oblib/src/lib && $(CMAKE_COMMAND) -P CMakeFiles/oblib_lib_coro_context.dir/cmake_clean.cmake
.PHONY : deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/clean

deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/depend:
	cd /home/spice/workspace/oceanbase && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/deps/oblib/src/lib /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/deps/oblib/src/lib /home/spice/workspace/oceanbase/deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : deps/oblib/src/lib/CMakeFiles/oblib_lib_coro_context.dir/depend

