# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mmc/mmorpg/cppSunnet

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mmc/mmorpg/cppSunnet/build

# Include any dependencies generated for this target.
include CMakeFiles/sunnet.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/sunnet.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/sunnet.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sunnet.dir/flags.make

CMakeFiles/sunnet.dir/src/Service.cpp.o: CMakeFiles/sunnet.dir/flags.make
CMakeFiles/sunnet.dir/src/Service.cpp.o: ../src/Service.cpp
CMakeFiles/sunnet.dir/src/Service.cpp.o: CMakeFiles/sunnet.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mmc/mmorpg/cppSunnet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sunnet.dir/src/Service.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sunnet.dir/src/Service.cpp.o -MF CMakeFiles/sunnet.dir/src/Service.cpp.o.d -o CMakeFiles/sunnet.dir/src/Service.cpp.o -c /home/mmc/mmorpg/cppSunnet/src/Service.cpp

CMakeFiles/sunnet.dir/src/Service.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sunnet.dir/src/Service.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mmc/mmorpg/cppSunnet/src/Service.cpp > CMakeFiles/sunnet.dir/src/Service.cpp.i

CMakeFiles/sunnet.dir/src/Service.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sunnet.dir/src/Service.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mmc/mmorpg/cppSunnet/src/Service.cpp -o CMakeFiles/sunnet.dir/src/Service.cpp.s

CMakeFiles/sunnet.dir/src/Sunnet.cpp.o: CMakeFiles/sunnet.dir/flags.make
CMakeFiles/sunnet.dir/src/Sunnet.cpp.o: ../src/Sunnet.cpp
CMakeFiles/sunnet.dir/src/Sunnet.cpp.o: CMakeFiles/sunnet.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mmc/mmorpg/cppSunnet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/sunnet.dir/src/Sunnet.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sunnet.dir/src/Sunnet.cpp.o -MF CMakeFiles/sunnet.dir/src/Sunnet.cpp.o.d -o CMakeFiles/sunnet.dir/src/Sunnet.cpp.o -c /home/mmc/mmorpg/cppSunnet/src/Sunnet.cpp

CMakeFiles/sunnet.dir/src/Sunnet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sunnet.dir/src/Sunnet.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mmc/mmorpg/cppSunnet/src/Sunnet.cpp > CMakeFiles/sunnet.dir/src/Sunnet.cpp.i

CMakeFiles/sunnet.dir/src/Sunnet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sunnet.dir/src/Sunnet.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mmc/mmorpg/cppSunnet/src/Sunnet.cpp -o CMakeFiles/sunnet.dir/src/Sunnet.cpp.s

CMakeFiles/sunnet.dir/src/Worker.cpp.o: CMakeFiles/sunnet.dir/flags.make
CMakeFiles/sunnet.dir/src/Worker.cpp.o: ../src/Worker.cpp
CMakeFiles/sunnet.dir/src/Worker.cpp.o: CMakeFiles/sunnet.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mmc/mmorpg/cppSunnet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/sunnet.dir/src/Worker.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sunnet.dir/src/Worker.cpp.o -MF CMakeFiles/sunnet.dir/src/Worker.cpp.o.d -o CMakeFiles/sunnet.dir/src/Worker.cpp.o -c /home/mmc/mmorpg/cppSunnet/src/Worker.cpp

CMakeFiles/sunnet.dir/src/Worker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sunnet.dir/src/Worker.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mmc/mmorpg/cppSunnet/src/Worker.cpp > CMakeFiles/sunnet.dir/src/Worker.cpp.i

CMakeFiles/sunnet.dir/src/Worker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sunnet.dir/src/Worker.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mmc/mmorpg/cppSunnet/src/Worker.cpp -o CMakeFiles/sunnet.dir/src/Worker.cpp.s

CMakeFiles/sunnet.dir/src/main.cpp.o: CMakeFiles/sunnet.dir/flags.make
CMakeFiles/sunnet.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/sunnet.dir/src/main.cpp.o: CMakeFiles/sunnet.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mmc/mmorpg/cppSunnet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/sunnet.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sunnet.dir/src/main.cpp.o -MF CMakeFiles/sunnet.dir/src/main.cpp.o.d -o CMakeFiles/sunnet.dir/src/main.cpp.o -c /home/mmc/mmorpg/cppSunnet/src/main.cpp

CMakeFiles/sunnet.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sunnet.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mmc/mmorpg/cppSunnet/src/main.cpp > CMakeFiles/sunnet.dir/src/main.cpp.i

CMakeFiles/sunnet.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sunnet.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mmc/mmorpg/cppSunnet/src/main.cpp -o CMakeFiles/sunnet.dir/src/main.cpp.s

# Object files for target sunnet
sunnet_OBJECTS = \
"CMakeFiles/sunnet.dir/src/Service.cpp.o" \
"CMakeFiles/sunnet.dir/src/Sunnet.cpp.o" \
"CMakeFiles/sunnet.dir/src/Worker.cpp.o" \
"CMakeFiles/sunnet.dir/src/main.cpp.o"

# External object files for target sunnet
sunnet_EXTERNAL_OBJECTS =

sunnet: CMakeFiles/sunnet.dir/src/Service.cpp.o
sunnet: CMakeFiles/sunnet.dir/src/Sunnet.cpp.o
sunnet: CMakeFiles/sunnet.dir/src/Worker.cpp.o
sunnet: CMakeFiles/sunnet.dir/src/main.cpp.o
sunnet: CMakeFiles/sunnet.dir/build.make
sunnet: CMakeFiles/sunnet.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mmc/mmorpg/cppSunnet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable sunnet"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sunnet.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sunnet.dir/build: sunnet
.PHONY : CMakeFiles/sunnet.dir/build

CMakeFiles/sunnet.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sunnet.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sunnet.dir/clean

CMakeFiles/sunnet.dir/depend:
	cd /home/mmc/mmorpg/cppSunnet/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mmc/mmorpg/cppSunnet /home/mmc/mmorpg/cppSunnet /home/mmc/mmorpg/cppSunnet/build /home/mmc/mmorpg/cppSunnet/build /home/mmc/mmorpg/cppSunnet/build/CMakeFiles/sunnet.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sunnet.dir/depend

