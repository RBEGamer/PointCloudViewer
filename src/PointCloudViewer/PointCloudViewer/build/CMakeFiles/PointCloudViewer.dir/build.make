# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer/build

# Include any dependencies generated for this target.
include CMakeFiles/PointCloudViewer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PointCloudViewer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PointCloudViewer.dir/flags.make

CMakeFiles/PointCloudViewer.dir/depth_device.cpp.o: CMakeFiles/PointCloudViewer.dir/flags.make
CMakeFiles/PointCloudViewer.dir/depth_device.cpp.o: ../depth_device.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PointCloudViewer.dir/depth_device.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PointCloudViewer.dir/depth_device.cpp.o -c /Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer/depth_device.cpp

CMakeFiles/PointCloudViewer.dir/depth_device.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PointCloudViewer.dir/depth_device.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer/depth_device.cpp > CMakeFiles/PointCloudViewer.dir/depth_device.cpp.i

CMakeFiles/PointCloudViewer.dir/depth_device.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PointCloudViewer.dir/depth_device.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer/depth_device.cpp -o CMakeFiles/PointCloudViewer.dir/depth_device.cpp.s

CMakeFiles/PointCloudViewer.dir/depth_device.cpp.o.requires:

.PHONY : CMakeFiles/PointCloudViewer.dir/depth_device.cpp.o.requires

CMakeFiles/PointCloudViewer.dir/depth_device.cpp.o.provides: CMakeFiles/PointCloudViewer.dir/depth_device.cpp.o.requires
	$(MAKE) -f CMakeFiles/PointCloudViewer.dir/build.make CMakeFiles/PointCloudViewer.dir/depth_device.cpp.o.provides.build
.PHONY : CMakeFiles/PointCloudViewer.dir/depth_device.cpp.o.provides

CMakeFiles/PointCloudViewer.dir/depth_device.cpp.o.provides.build: CMakeFiles/PointCloudViewer.dir/depth_device.cpp.o


CMakeFiles/PointCloudViewer.dir/depth_device_kinect_v2.cpp.o: CMakeFiles/PointCloudViewer.dir/flags.make
CMakeFiles/PointCloudViewer.dir/depth_device_kinect_v2.cpp.o: ../depth_device_kinect_v2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/PointCloudViewer.dir/depth_device_kinect_v2.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PointCloudViewer.dir/depth_device_kinect_v2.cpp.o -c /Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer/depth_device_kinect_v2.cpp

CMakeFiles/PointCloudViewer.dir/depth_device_kinect_v2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PointCloudViewer.dir/depth_device_kinect_v2.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer/depth_device_kinect_v2.cpp > CMakeFiles/PointCloudViewer.dir/depth_device_kinect_v2.cpp.i

CMakeFiles/PointCloudViewer.dir/depth_device_kinect_v2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PointCloudViewer.dir/depth_device_kinect_v2.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer/depth_device_kinect_v2.cpp -o CMakeFiles/PointCloudViewer.dir/depth_device_kinect_v2.cpp.s

CMakeFiles/PointCloudViewer.dir/depth_device_kinect_v2.cpp.o.requires:

.PHONY : CMakeFiles/PointCloudViewer.dir/depth_device_kinect_v2.cpp.o.requires

CMakeFiles/PointCloudViewer.dir/depth_device_kinect_v2.cpp.o.provides: CMakeFiles/PointCloudViewer.dir/depth_device_kinect_v2.cpp.o.requires
	$(MAKE) -f CMakeFiles/PointCloudViewer.dir/build.make CMakeFiles/PointCloudViewer.dir/depth_device_kinect_v2.cpp.o.provides.build
.PHONY : CMakeFiles/PointCloudViewer.dir/depth_device_kinect_v2.cpp.o.provides

CMakeFiles/PointCloudViewer.dir/depth_device_kinect_v2.cpp.o.provides.build: CMakeFiles/PointCloudViewer.dir/depth_device_kinect_v2.cpp.o


CMakeFiles/PointCloudViewer.dir/main.cpp.o: CMakeFiles/PointCloudViewer.dir/flags.make
CMakeFiles/PointCloudViewer.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/PointCloudViewer.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PointCloudViewer.dir/main.cpp.o -c /Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer/main.cpp

CMakeFiles/PointCloudViewer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PointCloudViewer.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer/main.cpp > CMakeFiles/PointCloudViewer.dir/main.cpp.i

CMakeFiles/PointCloudViewer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PointCloudViewer.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer/main.cpp -o CMakeFiles/PointCloudViewer.dir/main.cpp.s

CMakeFiles/PointCloudViewer.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/PointCloudViewer.dir/main.cpp.o.requires

CMakeFiles/PointCloudViewer.dir/main.cpp.o.provides: CMakeFiles/PointCloudViewer.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/PointCloudViewer.dir/build.make CMakeFiles/PointCloudViewer.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/PointCloudViewer.dir/main.cpp.o.provides

CMakeFiles/PointCloudViewer.dir/main.cpp.o.provides.build: CMakeFiles/PointCloudViewer.dir/main.cpp.o


CMakeFiles/PointCloudViewer.dir/primitive.cpp.o: CMakeFiles/PointCloudViewer.dir/flags.make
CMakeFiles/PointCloudViewer.dir/primitive.cpp.o: ../primitive.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/PointCloudViewer.dir/primitive.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PointCloudViewer.dir/primitive.cpp.o -c /Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer/primitive.cpp

CMakeFiles/PointCloudViewer.dir/primitive.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PointCloudViewer.dir/primitive.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer/primitive.cpp > CMakeFiles/PointCloudViewer.dir/primitive.cpp.i

CMakeFiles/PointCloudViewer.dir/primitive.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PointCloudViewer.dir/primitive.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer/primitive.cpp -o CMakeFiles/PointCloudViewer.dir/primitive.cpp.s

CMakeFiles/PointCloudViewer.dir/primitive.cpp.o.requires:

.PHONY : CMakeFiles/PointCloudViewer.dir/primitive.cpp.o.requires

CMakeFiles/PointCloudViewer.dir/primitive.cpp.o.provides: CMakeFiles/PointCloudViewer.dir/primitive.cpp.o.requires
	$(MAKE) -f CMakeFiles/PointCloudViewer.dir/build.make CMakeFiles/PointCloudViewer.dir/primitive.cpp.o.provides.build
.PHONY : CMakeFiles/PointCloudViewer.dir/primitive.cpp.o.provides

CMakeFiles/PointCloudViewer.dir/primitive.cpp.o.provides.build: CMakeFiles/PointCloudViewer.dir/primitive.cpp.o


CMakeFiles/PointCloudViewer.dir/primitive_cube.cpp.o: CMakeFiles/PointCloudViewer.dir/flags.make
CMakeFiles/PointCloudViewer.dir/primitive_cube.cpp.o: ../primitive_cube.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/PointCloudViewer.dir/primitive_cube.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PointCloudViewer.dir/primitive_cube.cpp.o -c /Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer/primitive_cube.cpp

CMakeFiles/PointCloudViewer.dir/primitive_cube.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PointCloudViewer.dir/primitive_cube.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer/primitive_cube.cpp > CMakeFiles/PointCloudViewer.dir/primitive_cube.cpp.i

CMakeFiles/PointCloudViewer.dir/primitive_cube.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PointCloudViewer.dir/primitive_cube.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer/primitive_cube.cpp -o CMakeFiles/PointCloudViewer.dir/primitive_cube.cpp.s

CMakeFiles/PointCloudViewer.dir/primitive_cube.cpp.o.requires:

.PHONY : CMakeFiles/PointCloudViewer.dir/primitive_cube.cpp.o.requires

CMakeFiles/PointCloudViewer.dir/primitive_cube.cpp.o.provides: CMakeFiles/PointCloudViewer.dir/primitive_cube.cpp.o.requires
	$(MAKE) -f CMakeFiles/PointCloudViewer.dir/build.make CMakeFiles/PointCloudViewer.dir/primitive_cube.cpp.o.provides.build
.PHONY : CMakeFiles/PointCloudViewer.dir/primitive_cube.cpp.o.provides

CMakeFiles/PointCloudViewer.dir/primitive_cube.cpp.o.provides.build: CMakeFiles/PointCloudViewer.dir/primitive_cube.cpp.o


# Object files for target PointCloudViewer
PointCloudViewer_OBJECTS = \
"CMakeFiles/PointCloudViewer.dir/depth_device.cpp.o" \
"CMakeFiles/PointCloudViewer.dir/depth_device_kinect_v2.cpp.o" \
"CMakeFiles/PointCloudViewer.dir/main.cpp.o" \
"CMakeFiles/PointCloudViewer.dir/primitive.cpp.o" \
"CMakeFiles/PointCloudViewer.dir/primitive_cube.cpp.o"

# External object files for target PointCloudViewer
PointCloudViewer_EXTERNAL_OBJECTS =

PointCloudViewer: CMakeFiles/PointCloudViewer.dir/depth_device.cpp.o
PointCloudViewer: CMakeFiles/PointCloudViewer.dir/depth_device_kinect_v2.cpp.o
PointCloudViewer: CMakeFiles/PointCloudViewer.dir/main.cpp.o
PointCloudViewer: CMakeFiles/PointCloudViewer.dir/primitive.cpp.o
PointCloudViewer: CMakeFiles/PointCloudViewer.dir/primitive_cube.cpp.o
PointCloudViewer: CMakeFiles/PointCloudViewer.dir/build.make
PointCloudViewer: CMakeFiles/PointCloudViewer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable PointCloudViewer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PointCloudViewer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PointCloudViewer.dir/build: PointCloudViewer

.PHONY : CMakeFiles/PointCloudViewer.dir/build

CMakeFiles/PointCloudViewer.dir/requires: CMakeFiles/PointCloudViewer.dir/depth_device.cpp.o.requires
CMakeFiles/PointCloudViewer.dir/requires: CMakeFiles/PointCloudViewer.dir/depth_device_kinect_v2.cpp.o.requires
CMakeFiles/PointCloudViewer.dir/requires: CMakeFiles/PointCloudViewer.dir/main.cpp.o.requires
CMakeFiles/PointCloudViewer.dir/requires: CMakeFiles/PointCloudViewer.dir/primitive.cpp.o.requires
CMakeFiles/PointCloudViewer.dir/requires: CMakeFiles/PointCloudViewer.dir/primitive_cube.cpp.o.requires

.PHONY : CMakeFiles/PointCloudViewer.dir/requires

CMakeFiles/PointCloudViewer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PointCloudViewer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PointCloudViewer.dir/clean

CMakeFiles/PointCloudViewer.dir/depend:
	cd /Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer /Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer /Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer/build /Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer/build /Users/marcelochsendorf/Desktop/PointCloudViewer/src/PointCloudViewer/PointCloudViewer/build/CMakeFiles/PointCloudViewer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PointCloudViewer.dir/depend
