# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/n3in/Workspace/cpp/project/project1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/n3in/Workspace/cpp/project/project1/build

# Include any dependencies generated for this target.
include CMakeFiles/project1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/project1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/project1.dir/flags.make

CMakeFiles/project1.dir/src/main.cpp.o: CMakeFiles/project1.dir/flags.make
CMakeFiles/project1.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/n3in/Workspace/cpp/project/project1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/project1.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project1.dir/src/main.cpp.o -c /home/n3in/Workspace/cpp/project/project1/src/main.cpp

CMakeFiles/project1.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project1.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/n3in/Workspace/cpp/project/project1/src/main.cpp > CMakeFiles/project1.dir/src/main.cpp.i

CMakeFiles/project1.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project1.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/n3in/Workspace/cpp/project/project1/src/main.cpp -o CMakeFiles/project1.dir/src/main.cpp.s

CMakeFiles/project1.dir/src/hero.cpp.o: CMakeFiles/project1.dir/flags.make
CMakeFiles/project1.dir/src/hero.cpp.o: ../src/hero.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/n3in/Workspace/cpp/project/project1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/project1.dir/src/hero.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project1.dir/src/hero.cpp.o -c /home/n3in/Workspace/cpp/project/project1/src/hero.cpp

CMakeFiles/project1.dir/src/hero.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project1.dir/src/hero.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/n3in/Workspace/cpp/project/project1/src/hero.cpp > CMakeFiles/project1.dir/src/hero.cpp.i

CMakeFiles/project1.dir/src/hero.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project1.dir/src/hero.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/n3in/Workspace/cpp/project/project1/src/hero.cpp -o CMakeFiles/project1.dir/src/hero.cpp.s

CMakeFiles/project1.dir/src/actor.cpp.o: CMakeFiles/project1.dir/flags.make
CMakeFiles/project1.dir/src/actor.cpp.o: ../src/actor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/n3in/Workspace/cpp/project/project1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/project1.dir/src/actor.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project1.dir/src/actor.cpp.o -c /home/n3in/Workspace/cpp/project/project1/src/actor.cpp

CMakeFiles/project1.dir/src/actor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project1.dir/src/actor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/n3in/Workspace/cpp/project/project1/src/actor.cpp > CMakeFiles/project1.dir/src/actor.cpp.i

CMakeFiles/project1.dir/src/actor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project1.dir/src/actor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/n3in/Workspace/cpp/project/project1/src/actor.cpp -o CMakeFiles/project1.dir/src/actor.cpp.s

CMakeFiles/project1.dir/src/actor_plusarmor.cpp.o: CMakeFiles/project1.dir/flags.make
CMakeFiles/project1.dir/src/actor_plusarmor.cpp.o: ../src/actor_plusarmor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/n3in/Workspace/cpp/project/project1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/project1.dir/src/actor_plusarmor.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project1.dir/src/actor_plusarmor.cpp.o -c /home/n3in/Workspace/cpp/project/project1/src/actor_plusarmor.cpp

CMakeFiles/project1.dir/src/actor_plusarmor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project1.dir/src/actor_plusarmor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/n3in/Workspace/cpp/project/project1/src/actor_plusarmor.cpp > CMakeFiles/project1.dir/src/actor_plusarmor.cpp.i

CMakeFiles/project1.dir/src/actor_plusarmor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project1.dir/src/actor_plusarmor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/n3in/Workspace/cpp/project/project1/src/actor_plusarmor.cpp -o CMakeFiles/project1.dir/src/actor_plusarmor.cpp.s

CMakeFiles/project1.dir/src/weapon.cpp.o: CMakeFiles/project1.dir/flags.make
CMakeFiles/project1.dir/src/weapon.cpp.o: ../src/weapon.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/n3in/Workspace/cpp/project/project1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/project1.dir/src/weapon.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project1.dir/src/weapon.cpp.o -c /home/n3in/Workspace/cpp/project/project1/src/weapon.cpp

CMakeFiles/project1.dir/src/weapon.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project1.dir/src/weapon.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/n3in/Workspace/cpp/project/project1/src/weapon.cpp > CMakeFiles/project1.dir/src/weapon.cpp.i

CMakeFiles/project1.dir/src/weapon.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project1.dir/src/weapon.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/n3in/Workspace/cpp/project/project1/src/weapon.cpp -o CMakeFiles/project1.dir/src/weapon.cpp.s

CMakeFiles/project1.dir/src/thegame.cpp.o: CMakeFiles/project1.dir/flags.make
CMakeFiles/project1.dir/src/thegame.cpp.o: ../src/thegame.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/n3in/Workspace/cpp/project/project1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/project1.dir/src/thegame.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project1.dir/src/thegame.cpp.o -c /home/n3in/Workspace/cpp/project/project1/src/thegame.cpp

CMakeFiles/project1.dir/src/thegame.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project1.dir/src/thegame.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/n3in/Workspace/cpp/project/project1/src/thegame.cpp > CMakeFiles/project1.dir/src/thegame.cpp.i

CMakeFiles/project1.dir/src/thegame.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project1.dir/src/thegame.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/n3in/Workspace/cpp/project/project1/src/thegame.cpp -o CMakeFiles/project1.dir/src/thegame.cpp.s

# Object files for target project1
project1_OBJECTS = \
"CMakeFiles/project1.dir/src/main.cpp.o" \
"CMakeFiles/project1.dir/src/hero.cpp.o" \
"CMakeFiles/project1.dir/src/actor.cpp.o" \
"CMakeFiles/project1.dir/src/actor_plusarmor.cpp.o" \
"CMakeFiles/project1.dir/src/weapon.cpp.o" \
"CMakeFiles/project1.dir/src/thegame.cpp.o"

# External object files for target project1
project1_EXTERNAL_OBJECTS =

project1: CMakeFiles/project1.dir/src/main.cpp.o
project1: CMakeFiles/project1.dir/src/hero.cpp.o
project1: CMakeFiles/project1.dir/src/actor.cpp.o
project1: CMakeFiles/project1.dir/src/actor_plusarmor.cpp.o
project1: CMakeFiles/project1.dir/src/weapon.cpp.o
project1: CMakeFiles/project1.dir/src/thegame.cpp.o
project1: CMakeFiles/project1.dir/build.make
project1: CMakeFiles/project1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/n3in/Workspace/cpp/project/project1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable project1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/project1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/project1.dir/build: project1

.PHONY : CMakeFiles/project1.dir/build

CMakeFiles/project1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/project1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/project1.dir/clean

CMakeFiles/project1.dir/depend:
	cd /home/n3in/Workspace/cpp/project/project1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/n3in/Workspace/cpp/project/project1 /home/n3in/Workspace/cpp/project/project1 /home/n3in/Workspace/cpp/project/project1/build /home/n3in/Workspace/cpp/project/project1/build /home/n3in/Workspace/cpp/project/project1/build/CMakeFiles/project1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/project1.dir/depend
