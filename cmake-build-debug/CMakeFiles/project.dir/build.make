# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /snap/clion/61/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/61/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/chaperone/data/ist/3Dprogramming/3D-Rendering

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chaperone/data/ist/3Dprogramming/3D-Rendering/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/project.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/project.dir/flags.make

CMakeFiles/project.dir/main.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chaperone/data/ist/3Dprogramming/3D-Rendering/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/project.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project.dir/main.cpp.o -c /home/chaperone/data/ist/3Dprogramming/3D-Rendering/main.cpp

CMakeFiles/project.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chaperone/data/ist/3Dprogramming/3D-Rendering/main.cpp > CMakeFiles/project.dir/main.cpp.i

CMakeFiles/project.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chaperone/data/ist/3Dprogramming/3D-Rendering/main.cpp -o CMakeFiles/project.dir/main.cpp.s

CMakeFiles/project.dir/Scene.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/Scene.cpp.o: ../Scene.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chaperone/data/ist/3Dprogramming/3D-Rendering/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/project.dir/Scene.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project.dir/Scene.cpp.o -c /home/chaperone/data/ist/3Dprogramming/3D-Rendering/Scene.cpp

CMakeFiles/project.dir/Scene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/Scene.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chaperone/data/ist/3Dprogramming/3D-Rendering/Scene.cpp > CMakeFiles/project.dir/Scene.cpp.i

CMakeFiles/project.dir/Scene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/Scene.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chaperone/data/ist/3Dprogramming/3D-Rendering/Scene.cpp -o CMakeFiles/project.dir/Scene.cpp.s

CMakeFiles/project.dir/Camera.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/Camera.cpp.o: ../Camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chaperone/data/ist/3Dprogramming/3D-Rendering/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/project.dir/Camera.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project.dir/Camera.cpp.o -c /home/chaperone/data/ist/3Dprogramming/3D-Rendering/Camera.cpp

CMakeFiles/project.dir/Camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/Camera.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chaperone/data/ist/3Dprogramming/3D-Rendering/Camera.cpp > CMakeFiles/project.dir/Camera.cpp.i

CMakeFiles/project.dir/Camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/Camera.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chaperone/data/ist/3Dprogramming/3D-Rendering/Camera.cpp -o CMakeFiles/project.dir/Camera.cpp.s

CMakeFiles/project.dir/Object.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/Object.cpp.o: ../Object.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chaperone/data/ist/3Dprogramming/3D-Rendering/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/project.dir/Object.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project.dir/Object.cpp.o -c /home/chaperone/data/ist/3Dprogramming/3D-Rendering/Object.cpp

CMakeFiles/project.dir/Object.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/Object.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chaperone/data/ist/3Dprogramming/3D-Rendering/Object.cpp > CMakeFiles/project.dir/Object.cpp.i

CMakeFiles/project.dir/Object.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/Object.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chaperone/data/ist/3Dprogramming/3D-Rendering/Object.cpp -o CMakeFiles/project.dir/Object.cpp.s

CMakeFiles/project.dir/Sphere.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/Sphere.cpp.o: ../Sphere.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chaperone/data/ist/3Dprogramming/3D-Rendering/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/project.dir/Sphere.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project.dir/Sphere.cpp.o -c /home/chaperone/data/ist/3Dprogramming/3D-Rendering/Sphere.cpp

CMakeFiles/project.dir/Sphere.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/Sphere.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chaperone/data/ist/3Dprogramming/3D-Rendering/Sphere.cpp > CMakeFiles/project.dir/Sphere.cpp.i

CMakeFiles/project.dir/Sphere.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/Sphere.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chaperone/data/ist/3Dprogramming/3D-Rendering/Sphere.cpp -o CMakeFiles/project.dir/Sphere.cpp.s

CMakeFiles/project.dir/Plane.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/Plane.cpp.o: ../Plane.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chaperone/data/ist/3Dprogramming/3D-Rendering/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/project.dir/Plane.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project.dir/Plane.cpp.o -c /home/chaperone/data/ist/3Dprogramming/3D-Rendering/Plane.cpp

CMakeFiles/project.dir/Plane.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/Plane.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chaperone/data/ist/3Dprogramming/3D-Rendering/Plane.cpp > CMakeFiles/project.dir/Plane.cpp.i

CMakeFiles/project.dir/Plane.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/Plane.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chaperone/data/ist/3Dprogramming/3D-Rendering/Plane.cpp -o CMakeFiles/project.dir/Plane.cpp.s

# Object files for target project
project_OBJECTS = \
"CMakeFiles/project.dir/main.cpp.o" \
"CMakeFiles/project.dir/Scene.cpp.o" \
"CMakeFiles/project.dir/Camera.cpp.o" \
"CMakeFiles/project.dir/Object.cpp.o" \
"CMakeFiles/project.dir/Sphere.cpp.o" \
"CMakeFiles/project.dir/Plane.cpp.o"

# External object files for target project
project_EXTERNAL_OBJECTS =

project: CMakeFiles/project.dir/main.cpp.o
project: CMakeFiles/project.dir/Scene.cpp.o
project: CMakeFiles/project.dir/Camera.cpp.o
project: CMakeFiles/project.dir/Object.cpp.o
project: CMakeFiles/project.dir/Sphere.cpp.o
project: CMakeFiles/project.dir/Plane.cpp.o
project: CMakeFiles/project.dir/build.make
project: CMakeFiles/project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chaperone/data/ist/3Dprogramming/3D-Rendering/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/project.dir/build: project

.PHONY : CMakeFiles/project.dir/build

CMakeFiles/project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/project.dir/clean

CMakeFiles/project.dir/depend:
	cd /home/chaperone/data/ist/3Dprogramming/3D-Rendering/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chaperone/data/ist/3Dprogramming/3D-Rendering /home/chaperone/data/ist/3Dprogramming/3D-Rendering /home/chaperone/data/ist/3Dprogramming/3D-Rendering/cmake-build-debug /home/chaperone/data/ist/3Dprogramming/3D-Rendering/cmake-build-debug /home/chaperone/data/ist/3Dprogramming/3D-Rendering/cmake-build-debug/CMakeFiles/project.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/project.dir/depend

