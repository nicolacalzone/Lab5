# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/nicola/opencv/Lab5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nicola/opencv/Lab5/build

# Include any dependencies generated for this target.
include CMakeFiles/Lab5.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Lab5.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Lab5.dir/flags.make

CMakeFiles/Lab5.dir/task1.cpp.o: CMakeFiles/Lab5.dir/flags.make
CMakeFiles/Lab5.dir/task1.cpp.o: ../task1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nicola/opencv/Lab5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Lab5.dir/task1.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Lab5.dir/task1.cpp.o -c /home/nicola/opencv/Lab5/task1.cpp

CMakeFiles/Lab5.dir/task1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab5.dir/task1.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nicola/opencv/Lab5/task1.cpp > CMakeFiles/Lab5.dir/task1.cpp.i

CMakeFiles/Lab5.dir/task1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab5.dir/task1.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nicola/opencv/Lab5/task1.cpp -o CMakeFiles/Lab5.dir/task1.cpp.s

CMakeFiles/Lab5.dir/task1.cpp.o.requires:

.PHONY : CMakeFiles/Lab5.dir/task1.cpp.o.requires

CMakeFiles/Lab5.dir/task1.cpp.o.provides: CMakeFiles/Lab5.dir/task1.cpp.o.requires
	$(MAKE) -f CMakeFiles/Lab5.dir/build.make CMakeFiles/Lab5.dir/task1.cpp.o.provides.build
.PHONY : CMakeFiles/Lab5.dir/task1.cpp.o.provides

CMakeFiles/Lab5.dir/task1.cpp.o.provides.build: CMakeFiles/Lab5.dir/task1.cpp.o


# Object files for target Lab5
Lab5_OBJECTS = \
"CMakeFiles/Lab5.dir/task1.cpp.o"

# External object files for target Lab5
Lab5_EXTERNAL_OBJECTS =

Lab5: CMakeFiles/Lab5.dir/task1.cpp.o
Lab5: CMakeFiles/Lab5.dir/build.make
Lab5: /usr/local/lib/libopencv_gapi.so.4.7.0
Lab5: /usr/local/lib/libopencv_highgui.so.4.7.0
Lab5: /usr/local/lib/libopencv_ml.so.4.7.0
Lab5: /usr/local/lib/libopencv_objdetect.so.4.7.0
Lab5: /usr/local/lib/libopencv_photo.so.4.7.0
Lab5: /usr/local/lib/libopencv_stitching.so.4.7.0
Lab5: /usr/local/lib/libopencv_video.so.4.7.0
Lab5: /usr/local/lib/libopencv_videoio.so.4.7.0
Lab5: /usr/local/lib/libopencv_imgcodecs.so.4.7.0
Lab5: /usr/local/lib/libopencv_dnn.so.4.7.0
Lab5: /usr/local/lib/libopencv_calib3d.so.4.7.0
Lab5: /usr/local/lib/libopencv_features2d.so.4.7.0
Lab5: /usr/local/lib/libopencv_flann.so.4.7.0
Lab5: /usr/local/lib/libopencv_imgproc.so.4.7.0
Lab5: /usr/local/lib/libopencv_core.so.4.7.0
Lab5: CMakeFiles/Lab5.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nicola/opencv/Lab5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Lab5"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Lab5.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Lab5.dir/build: Lab5

.PHONY : CMakeFiles/Lab5.dir/build

CMakeFiles/Lab5.dir/requires: CMakeFiles/Lab5.dir/task1.cpp.o.requires

.PHONY : CMakeFiles/Lab5.dir/requires

CMakeFiles/Lab5.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Lab5.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Lab5.dir/clean

CMakeFiles/Lab5.dir/depend:
	cd /home/nicola/opencv/Lab5/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nicola/opencv/Lab5 /home/nicola/opencv/Lab5 /home/nicola/opencv/Lab5/build /home/nicola/opencv/Lab5/build /home/nicola/opencv/Lab5/build/CMakeFiles/Lab5.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Lab5.dir/depend

