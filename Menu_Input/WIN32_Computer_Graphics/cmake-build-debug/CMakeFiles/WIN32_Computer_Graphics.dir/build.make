# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.3.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.3.2\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = S:\faculty\github\WIN32_Computer_Graphics\Menu_Input\WIN32_Computer_Graphics

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = S:\faculty\github\WIN32_Computer_Graphics\Menu_Input\WIN32_Computer_Graphics\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/WIN32_Computer_Graphics.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/WIN32_Computer_Graphics.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/WIN32_Computer_Graphics.dir/flags.make

CMakeFiles/WIN32_Computer_Graphics.dir/main.cpp.obj: CMakeFiles/WIN32_Computer_Graphics.dir/flags.make
CMakeFiles/WIN32_Computer_Graphics.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=S:\faculty\github\WIN32_Computer_Graphics\Menu_Input\WIN32_Computer_Graphics\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/WIN32_Computer_Graphics.dir/main.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\WIN32_Computer_Graphics.dir\main.cpp.obj -c S:\faculty\github\WIN32_Computer_Graphics\Menu_Input\WIN32_Computer_Graphics\main.cpp

CMakeFiles/WIN32_Computer_Graphics.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WIN32_Computer_Graphics.dir/main.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E S:\faculty\github\WIN32_Computer_Graphics\Menu_Input\WIN32_Computer_Graphics\main.cpp > CMakeFiles\WIN32_Computer_Graphics.dir\main.cpp.i

CMakeFiles/WIN32_Computer_Graphics.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WIN32_Computer_Graphics.dir/main.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S S:\faculty\github\WIN32_Computer_Graphics\Menu_Input\WIN32_Computer_Graphics\main.cpp -o CMakeFiles\WIN32_Computer_Graphics.dir\main.cpp.s

# Object files for target WIN32_Computer_Graphics
WIN32_Computer_Graphics_OBJECTS = \
"CMakeFiles/WIN32_Computer_Graphics.dir/main.cpp.obj"

# External object files for target WIN32_Computer_Graphics
WIN32_Computer_Graphics_EXTERNAL_OBJECTS =

WIN32_Computer_Graphics.exe: CMakeFiles/WIN32_Computer_Graphics.dir/main.cpp.obj
WIN32_Computer_Graphics.exe: CMakeFiles/WIN32_Computer_Graphics.dir/build.make
WIN32_Computer_Graphics.exe: CMakeFiles/WIN32_Computer_Graphics.dir/linklibs.rsp
WIN32_Computer_Graphics.exe: CMakeFiles/WIN32_Computer_Graphics.dir/objects1.rsp
WIN32_Computer_Graphics.exe: CMakeFiles/WIN32_Computer_Graphics.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=S:\faculty\github\WIN32_Computer_Graphics\Menu_Input\WIN32_Computer_Graphics\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable WIN32_Computer_Graphics.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\WIN32_Computer_Graphics.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/WIN32_Computer_Graphics.dir/build: WIN32_Computer_Graphics.exe

.PHONY : CMakeFiles/WIN32_Computer_Graphics.dir/build

CMakeFiles/WIN32_Computer_Graphics.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\WIN32_Computer_Graphics.dir\cmake_clean.cmake
.PHONY : CMakeFiles/WIN32_Computer_Graphics.dir/clean

CMakeFiles/WIN32_Computer_Graphics.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" S:\faculty\github\WIN32_Computer_Graphics\Menu_Input\WIN32_Computer_Graphics S:\faculty\github\WIN32_Computer_Graphics\Menu_Input\WIN32_Computer_Graphics S:\faculty\github\WIN32_Computer_Graphics\Menu_Input\WIN32_Computer_Graphics\cmake-build-debug S:\faculty\github\WIN32_Computer_Graphics\Menu_Input\WIN32_Computer_Graphics\cmake-build-debug S:\faculty\github\WIN32_Computer_Graphics\Menu_Input\WIN32_Computer_Graphics\cmake-build-debug\CMakeFiles\WIN32_Computer_Graphics.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/WIN32_Computer_Graphics.dir/depend
