# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_SOURCE_DIR = /home/teo/jr3pciYarp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/teo/jr3pciYarp/build

# Include any dependencies generated for this target.
include CMakeFiles/jr3pciYarp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/jr3pciYarp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/jr3pciYarp.dir/flags.make

CMakeFiles/jr3pciYarp.dir/main.cpp.o: CMakeFiles/jr3pciYarp.dir/flags.make
CMakeFiles/jr3pciYarp.dir/main.cpp.o: ../main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/teo/jr3pciYarp/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/jr3pciYarp.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/jr3pciYarp.dir/main.cpp.o -c /home/teo/jr3pciYarp/main.cpp

CMakeFiles/jr3pciYarp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jr3pciYarp.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/teo/jr3pciYarp/main.cpp > CMakeFiles/jr3pciYarp.dir/main.cpp.i

CMakeFiles/jr3pciYarp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jr3pciYarp.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/teo/jr3pciYarp/main.cpp -o CMakeFiles/jr3pciYarp.dir/main.cpp.s

CMakeFiles/jr3pciYarp.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/jr3pciYarp.dir/main.cpp.o.requires

CMakeFiles/jr3pciYarp.dir/main.cpp.o.provides: CMakeFiles/jr3pciYarp.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/jr3pciYarp.dir/build.make CMakeFiles/jr3pciYarp.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/jr3pciYarp.dir/main.cpp.o.provides

CMakeFiles/jr3pciYarp.dir/main.cpp.o.provides.build: CMakeFiles/jr3pciYarp.dir/main.cpp.o

# Object files for target jr3pciYarp
jr3pciYarp_OBJECTS = \
"CMakeFiles/jr3pciYarp.dir/main.cpp.o"

# External object files for target jr3pciYarp
jr3pciYarp_EXTERNAL_OBJECTS =

jr3pciYarp: CMakeFiles/jr3pciYarp.dir/main.cpp.o
jr3pciYarp: CMakeFiles/jr3pciYarp.dir/build.make
jr3pciYarp: /usr/local/lib/libYARP_OS.so.2.3.64.7
jr3pciYarp: /usr/local/lib/libYARP_sig.so.2.3.64.7
jr3pciYarp: /usr/local/lib/libYARP_math.so.2.3.64.7
jr3pciYarp: /usr/local/lib/libYARP_dev.so.2.3.64.7
jr3pciYarp: /usr/local/lib/libYARP_init.so.2.3.64.7
jr3pciYarp: /usr/local/lib/libYARP_name.so.2.3.64.7
jr3pciYarp: /usr/local/lib/libYARP_sig.so.2.3.64.7
jr3pciYarp: /usr/local/lib/libYARP_OS.so.2.3.64.7
jr3pciYarp: CMakeFiles/jr3pciYarp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable jr3pciYarp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jr3pciYarp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/jr3pciYarp.dir/build: jr3pciYarp
.PHONY : CMakeFiles/jr3pciYarp.dir/build

CMakeFiles/jr3pciYarp.dir/requires: CMakeFiles/jr3pciYarp.dir/main.cpp.o.requires
.PHONY : CMakeFiles/jr3pciYarp.dir/requires

CMakeFiles/jr3pciYarp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/jr3pciYarp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/jr3pciYarp.dir/clean

CMakeFiles/jr3pciYarp.dir/depend:
	cd /home/teo/jr3pciYarp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/teo/jr3pciYarp /home/teo/jr3pciYarp /home/teo/jr3pciYarp/build /home/teo/jr3pciYarp/build /home/teo/jr3pciYarp/build/CMakeFiles/jr3pciYarp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/jr3pciYarp.dir/depend
