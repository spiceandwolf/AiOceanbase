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
include src/rootserver/CMakeFiles/ob_rootserver.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/rootserver/CMakeFiles/ob_rootserver.dir/compiler_depend.make

# Include the progress variables for this target.
include src/rootserver/CMakeFiles/ob_rootserver.dir/progress.make

# Include the compile flags for this target's objects.
include src/rootserver/CMakeFiles/ob_rootserver.dir/flags.make

src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/0_cxx.cxx.o: src/rootserver/CMakeFiles/ob_rootserver.dir/flags.make
src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/0_cxx.cxx.o: src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/0_cxx.cxx
src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/0_cxx.cxx.o: src/CMakeFiles/server_pch.dir/cmake_pch.hxx
src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/0_cxx.cxx.o: src/CMakeFiles/server_pch.dir/cmake_pch.hxx.pch
src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/0_cxx.cxx.o: src/rootserver/CMakeFiles/ob_rootserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/0_cxx.cxx.o"
	cd /home/spice/workspace/oceanbase/src/rootserver && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx -MD -MT src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/0_cxx.cxx.o -MF CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/0_cxx.cxx.o.d -o CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/0_cxx.cxx.o -c /home/spice/workspace/oceanbase/src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/0_cxx.cxx

src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/0_cxx.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/0_cxx.cxx.i"
	cd /home/spice/workspace/oceanbase/src/rootserver && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx -E /home/spice/workspace/oceanbase/src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/0_cxx.cxx > CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/0_cxx.cxx.i

src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/0_cxx.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/0_cxx.cxx.s"
	cd /home/spice/workspace/oceanbase/src/rootserver && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx -S /home/spice/workspace/oceanbase/src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/0_cxx.cxx -o CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/0_cxx.cxx.s

src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_backup/0_cxx.cxx.o: src/rootserver/CMakeFiles/ob_rootserver.dir/flags.make
src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_backup/0_cxx.cxx.o: src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_backup/0_cxx.cxx
src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_backup/0_cxx.cxx.o: src/CMakeFiles/server_pch.dir/cmake_pch.hxx
src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_backup/0_cxx.cxx.o: src/CMakeFiles/server_pch.dir/cmake_pch.hxx.pch
src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_backup/0_cxx.cxx.o: src/rootserver/CMakeFiles/ob_rootserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_backup/0_cxx.cxx.o"
	cd /home/spice/workspace/oceanbase/src/rootserver && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx -MD -MT src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_backup/0_cxx.cxx.o -MF CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_backup/0_cxx.cxx.o.d -o CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_backup/0_cxx.cxx.o -c /home/spice/workspace/oceanbase/src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_backup/0_cxx.cxx

src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_backup/0_cxx.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_backup/0_cxx.cxx.i"
	cd /home/spice/workspace/oceanbase/src/rootserver && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx -E /home/spice/workspace/oceanbase/src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_backup/0_cxx.cxx > CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_backup/0_cxx.cxx.i

src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_backup/0_cxx.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_backup/0_cxx.cxx.s"
	cd /home/spice/workspace/oceanbase/src/rootserver && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx -S /home/spice/workspace/oceanbase/src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_backup/0_cxx.cxx -o CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_backup/0_cxx.cxx.s

src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/1_cxx.cxx.o: src/rootserver/CMakeFiles/ob_rootserver.dir/flags.make
src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/1_cxx.cxx.o: src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/1_cxx.cxx
src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/1_cxx.cxx.o: src/CMakeFiles/server_pch.dir/cmake_pch.hxx
src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/1_cxx.cxx.o: src/CMakeFiles/server_pch.dir/cmake_pch.hxx.pch
src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/1_cxx.cxx.o: src/rootserver/CMakeFiles/ob_rootserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/1_cxx.cxx.o"
	cd /home/spice/workspace/oceanbase/src/rootserver && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx -MD -MT src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/1_cxx.cxx.o -MF CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/1_cxx.cxx.o.d -o CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/1_cxx.cxx.o -c /home/spice/workspace/oceanbase/src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/1_cxx.cxx

src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/1_cxx.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/1_cxx.cxx.i"
	cd /home/spice/workspace/oceanbase/src/rootserver && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx -E /home/spice/workspace/oceanbase/src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/1_cxx.cxx > CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/1_cxx.cxx.i

src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/1_cxx.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/1_cxx.cxx.s"
	cd /home/spice/workspace/oceanbase/src/rootserver && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx -S /home/spice/workspace/oceanbase/src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/1_cxx.cxx -o CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/1_cxx.cxx.s

src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/0_cxx.cxx.o: src/rootserver/CMakeFiles/ob_rootserver.dir/flags.make
src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/0_cxx.cxx.o: src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/0_cxx.cxx
src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/0_cxx.cxx.o: src/CMakeFiles/server_pch.dir/cmake_pch.hxx
src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/0_cxx.cxx.o: src/CMakeFiles/server_pch.dir/cmake_pch.hxx.pch
src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/0_cxx.cxx.o: src/rootserver/CMakeFiles/ob_rootserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/0_cxx.cxx.o"
	cd /home/spice/workspace/oceanbase/src/rootserver && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx -MD -MT src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/0_cxx.cxx.o -MF CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/0_cxx.cxx.o.d -o CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/0_cxx.cxx.o -c /home/spice/workspace/oceanbase/src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/0_cxx.cxx

src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/0_cxx.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/0_cxx.cxx.i"
	cd /home/spice/workspace/oceanbase/src/rootserver && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx -E /home/spice/workspace/oceanbase/src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/0_cxx.cxx > CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/0_cxx.cxx.i

src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/0_cxx.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/0_cxx.cxx.s"
	cd /home/spice/workspace/oceanbase/src/rootserver && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx -S /home/spice/workspace/oceanbase/src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/0_cxx.cxx -o CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/0_cxx.cxx.s

src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_vt/0_cxx.cxx.o: src/rootserver/CMakeFiles/ob_rootserver.dir/flags.make
src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_vt/0_cxx.cxx.o: src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_vt/0_cxx.cxx
src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_vt/0_cxx.cxx.o: src/CMakeFiles/server_pch.dir/cmake_pch.hxx
src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_vt/0_cxx.cxx.o: src/CMakeFiles/server_pch.dir/cmake_pch.hxx.pch
src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_vt/0_cxx.cxx.o: src/rootserver/CMakeFiles/ob_rootserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_vt/0_cxx.cxx.o"
	cd /home/spice/workspace/oceanbase/src/rootserver && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx -MD -MT src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_vt/0_cxx.cxx.o -MF CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_vt/0_cxx.cxx.o.d -o CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_vt/0_cxx.cxx.o -c /home/spice/workspace/oceanbase/src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_vt/0_cxx.cxx

src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_vt/0_cxx.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_vt/0_cxx.cxx.i"
	cd /home/spice/workspace/oceanbase/src/rootserver && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx -E /home/spice/workspace/oceanbase/src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_vt/0_cxx.cxx > CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_vt/0_cxx.cxx.i

src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_vt/0_cxx.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_vt/0_cxx.cxx.s"
	cd /home/spice/workspace/oceanbase/src/rootserver && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx -S /home/spice/workspace/oceanbase/src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_vt/0_cxx.cxx -o CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_vt/0_cxx.cxx.s

src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_restore/0_cxx.cxx.o: src/rootserver/CMakeFiles/ob_rootserver.dir/flags.make
src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_restore/0_cxx.cxx.o: src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_restore/0_cxx.cxx
src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_restore/0_cxx.cxx.o: src/CMakeFiles/server_pch.dir/cmake_pch.hxx
src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_restore/0_cxx.cxx.o: src/CMakeFiles/server_pch.dir/cmake_pch.hxx.pch
src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_restore/0_cxx.cxx.o: src/rootserver/CMakeFiles/ob_rootserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_restore/0_cxx.cxx.o"
	cd /home/spice/workspace/oceanbase/src/rootserver && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx -MD -MT src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_restore/0_cxx.cxx.o -MF CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_restore/0_cxx.cxx.o.d -o CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_restore/0_cxx.cxx.o -c /home/spice/workspace/oceanbase/src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_restore/0_cxx.cxx

src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_restore/0_cxx.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_restore/0_cxx.cxx.i"
	cd /home/spice/workspace/oceanbase/src/rootserver && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx -E /home/spice/workspace/oceanbase/src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_restore/0_cxx.cxx > CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_restore/0_cxx.cxx.i

src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_restore/0_cxx.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_restore/0_cxx.cxx.s"
	cd /home/spice/workspace/oceanbase/src/rootserver && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx -S /home/spice/workspace/oceanbase/src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_restore/0_cxx.cxx -o CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_restore/0_cxx.cxx.s

src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/1_cxx.cxx.o: src/rootserver/CMakeFiles/ob_rootserver.dir/flags.make
src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/1_cxx.cxx.o: src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/1_cxx.cxx
src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/1_cxx.cxx.o: src/CMakeFiles/server_pch.dir/cmake_pch.hxx
src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/1_cxx.cxx.o: src/CMakeFiles/server_pch.dir/cmake_pch.hxx.pch
src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/1_cxx.cxx.o: src/rootserver/CMakeFiles/ob_rootserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spice/workspace/oceanbase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/1_cxx.cxx.o"
	cd /home/spice/workspace/oceanbase/src/rootserver && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx -MD -MT src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/1_cxx.cxx.o -MF CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/1_cxx.cxx.o.d -o CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/1_cxx.cxx.o -c /home/spice/workspace/oceanbase/src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/1_cxx.cxx

src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/1_cxx.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/1_cxx.cxx.i"
	cd /home/spice/workspace/oceanbase/src/rootserver && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx -E /home/spice/workspace/oceanbase/src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/1_cxx.cxx > CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/1_cxx.cxx.i

src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/1_cxx.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/1_cxx.cxx.s"
	cd /home/spice/workspace/oceanbase/src/rootserver && /home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/devtools/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xclang -include-pch -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx.pch -Xclang -include -Xclang /home/spice/workspace/oceanbase/src/CMakeFiles/server_pch.dir/cmake_pch.hxx -S /home/spice/workspace/oceanbase/src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/1_cxx.cxx -o CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/1_cxx.cxx.s

ob_rootserver: src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/0_cxx.cxx.o
ob_rootserver: src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_backup/0_cxx.cxx.o
ob_rootserver: src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_common/1_cxx.cxx.o
ob_rootserver: src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/0_cxx.cxx.o
ob_rootserver: src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_vt/0_cxx.cxx.o
ob_rootserver: src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_restore/0_cxx.cxx.o
ob_rootserver: src/rootserver/CMakeFiles/ob_rootserver.dir/Unity/unity_ob_rootserver_task/1_cxx.cxx.o
ob_rootserver: src/rootserver/CMakeFiles/ob_rootserver.dir/build.make
.PHONY : ob_rootserver

# Rule to build all files generated by this target.
src/rootserver/CMakeFiles/ob_rootserver.dir/build: ob_rootserver
.PHONY : src/rootserver/CMakeFiles/ob_rootserver.dir/build

src/rootserver/CMakeFiles/ob_rootserver.dir/clean:
	cd /home/spice/workspace/oceanbase/src/rootserver && $(CMAKE_COMMAND) -P CMakeFiles/ob_rootserver.dir/cmake_clean.cmake
.PHONY : src/rootserver/CMakeFiles/ob_rootserver.dir/clean

src/rootserver/CMakeFiles/ob_rootserver.dir/depend:
	cd /home/spice/workspace/oceanbase && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/src/rootserver /home/spice/workspace/oceanbase /home/spice/workspace/oceanbase/src/rootserver /home/spice/workspace/oceanbase/src/rootserver/CMakeFiles/ob_rootserver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/rootserver/CMakeFiles/ob_rootserver.dir/depend

