# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/brad/workspace/seniorProjoct/poropy/poropy_core

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/brad/workspace/seniorProjoct/poropy/poropy_core

# Include any dependencies generated for this target.
include src/CMakeFiles/_poropy_core.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/_poropy_core.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/_poropy_core.dir/flags.make

src/poropyPYTHON_wrap.cxx: src/poropy.i
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/brad/workspace/seniorProjoct/poropy/poropy_core/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Swig source"
	cd /home/brad/workspace/seniorProjoct/poropy/poropy_core/src && /usr/bin/cmake -E make_directory /home/brad/workspace/seniorProjoct/poropy/poropy_core/src
	cd /home/brad/workspace/seniorProjoct/poropy/poropy_core/src && /usr/bin/swig3.0 -python -v -outdir /home/brad/workspace/seniorProjoct/poropy/poropy_core/src -c++ -I/home/brad/opt/conda/include/python3.5 -I/home/brad/workspace/seniorProjoct/poropy/poropy_core/config -I/home/brad/workspace/seniorProjoct/poropy/poropy_core/src -o /home/brad/workspace/seniorProjoct/poropy/poropy_core/src/poropyPYTHON_wrap.cxx /home/brad/workspace/seniorProjoct/poropy/poropy_core/src/poropy.i

src/poropy_core.py: src/poropyPYTHON_wrap.cxx
	@$(CMAKE_COMMAND) -E touch_nocreate src/poropy_core.py

src/CMakeFiles/_poropy_core.dir/poropyPYTHON_wrap.cxx.o: src/CMakeFiles/_poropy_core.dir/flags.make
src/CMakeFiles/_poropy_core.dir/poropyPYTHON_wrap.cxx.o: src/poropyPYTHON_wrap.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brad/workspace/seniorProjoct/poropy/poropy_core/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/_poropy_core.dir/poropyPYTHON_wrap.cxx.o"
	cd /home/brad/workspace/seniorProjoct/poropy/poropy_core/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/_poropy_core.dir/poropyPYTHON_wrap.cxx.o -c /home/brad/workspace/seniorProjoct/poropy/poropy_core/src/poropyPYTHON_wrap.cxx

src/CMakeFiles/_poropy_core.dir/poropyPYTHON_wrap.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/_poropy_core.dir/poropyPYTHON_wrap.cxx.i"
	cd /home/brad/workspace/seniorProjoct/poropy/poropy_core/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brad/workspace/seniorProjoct/poropy/poropy_core/src/poropyPYTHON_wrap.cxx > CMakeFiles/_poropy_core.dir/poropyPYTHON_wrap.cxx.i

src/CMakeFiles/_poropy_core.dir/poropyPYTHON_wrap.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/_poropy_core.dir/poropyPYTHON_wrap.cxx.s"
	cd /home/brad/workspace/seniorProjoct/poropy/poropy_core/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brad/workspace/seniorProjoct/poropy/poropy_core/src/poropyPYTHON_wrap.cxx -o CMakeFiles/_poropy_core.dir/poropyPYTHON_wrap.cxx.s

src/CMakeFiles/_poropy_core.dir/poropyPYTHON_wrap.cxx.o.requires:

.PHONY : src/CMakeFiles/_poropy_core.dir/poropyPYTHON_wrap.cxx.o.requires

src/CMakeFiles/_poropy_core.dir/poropyPYTHON_wrap.cxx.o.provides: src/CMakeFiles/_poropy_core.dir/poropyPYTHON_wrap.cxx.o.requires
	$(MAKE) -f src/CMakeFiles/_poropy_core.dir/build.make src/CMakeFiles/_poropy_core.dir/poropyPYTHON_wrap.cxx.o.provides.build
.PHONY : src/CMakeFiles/_poropy_core.dir/poropyPYTHON_wrap.cxx.o.provides

src/CMakeFiles/_poropy_core.dir/poropyPYTHON_wrap.cxx.o.provides.build: src/CMakeFiles/_poropy_core.dir/poropyPYTHON_wrap.cxx.o


# Object files for target _poropy_core
_poropy_core_OBJECTS = \
"CMakeFiles/_poropy_core.dir/poropyPYTHON_wrap.cxx.o"

# External object files for target _poropy_core
_poropy_core_EXTERNAL_OBJECTS =

src/_poropy_core.so: src/CMakeFiles/_poropy_core.dir/poropyPYTHON_wrap.cxx.o
src/_poropy_core.so: src/CMakeFiles/_poropy_core.dir/build.make
src/_poropy_core.so: /usr/lib/x86_64-linux-gnu/libpython3.5.so
src/_poropy_core.so: src/libporopy_core.so
src/_poropy_core.so: src/CMakeFiles/_poropy_core.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/brad/workspace/seniorProjoct/poropy/poropy_core/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared module _poropy_core.so"
	cd /home/brad/workspace/seniorProjoct/poropy/poropy_core/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/_poropy_core.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/_poropy_core.dir/build: src/_poropy_core.so

.PHONY : src/CMakeFiles/_poropy_core.dir/build

src/CMakeFiles/_poropy_core.dir/requires: src/CMakeFiles/_poropy_core.dir/poropyPYTHON_wrap.cxx.o.requires

.PHONY : src/CMakeFiles/_poropy_core.dir/requires

src/CMakeFiles/_poropy_core.dir/clean:
	cd /home/brad/workspace/seniorProjoct/poropy/poropy_core/src && $(CMAKE_COMMAND) -P CMakeFiles/_poropy_core.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/_poropy_core.dir/clean

src/CMakeFiles/_poropy_core.dir/depend: src/poropyPYTHON_wrap.cxx
src/CMakeFiles/_poropy_core.dir/depend: src/poropy_core.py
	cd /home/brad/workspace/seniorProjoct/poropy/poropy_core && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/brad/workspace/seniorProjoct/poropy/poropy_core /home/brad/workspace/seniorProjoct/poropy/poropy_core/src /home/brad/workspace/seniorProjoct/poropy/poropy_core /home/brad/workspace/seniorProjoct/poropy/poropy_core/src /home/brad/workspace/seniorProjoct/poropy/poropy_core/src/CMakeFiles/_poropy_core.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/_poropy_core.dir/depend

