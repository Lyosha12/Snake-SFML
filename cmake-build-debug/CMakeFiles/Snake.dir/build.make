# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = "W:\Programs\Programming environment\IDEs\CLion 2018.1.4\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "W:\Programs\Programming environment\IDEs\CLion 2018.1.4\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "W:\Programs\Programming environment\Projects\Fun\Snake"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "W:\Programs\Programming environment\Projects\Fun\Snake\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Snake.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Snake.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Snake.dir/flags.make

CMakeFiles/Snake.dir/main.cpp.obj: CMakeFiles/Snake.dir/flags.make
CMakeFiles/Snake.dir/main.cpp.obj: CMakeFiles/Snake.dir/includes_CXX.rsp
CMakeFiles/Snake.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="W:\Programs\Programming environment\Projects\Fun\Snake\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Snake.dir/main.cpp.obj"
	W:\Programs\PROGRA~1\COMPIL~1\MINGW3~1.0-P\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Snake.dir\main.cpp.obj -c "W:\Programs\Programming environment\Projects\Fun\Snake\main.cpp"

CMakeFiles/Snake.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Snake.dir/main.cpp.i"
	W:\Programs\PROGRA~1\COMPIL~1\MINGW3~1.0-P\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "W:\Programs\Programming environment\Projects\Fun\Snake\main.cpp" > CMakeFiles\Snake.dir\main.cpp.i

CMakeFiles/Snake.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Snake.dir/main.cpp.s"
	W:\Programs\PROGRA~1\COMPIL~1\MINGW3~1.0-P\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "W:\Programs\Programming environment\Projects\Fun\Snake\main.cpp" -o CMakeFiles\Snake.dir\main.cpp.s

CMakeFiles/Snake.dir/main.cpp.obj.requires:

.PHONY : CMakeFiles/Snake.dir/main.cpp.obj.requires

CMakeFiles/Snake.dir/main.cpp.obj.provides: CMakeFiles/Snake.dir/main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\Snake.dir\build.make CMakeFiles/Snake.dir/main.cpp.obj.provides.build
.PHONY : CMakeFiles/Snake.dir/main.cpp.obj.provides

CMakeFiles/Snake.dir/main.cpp.obj.provides.build: CMakeFiles/Snake.dir/main.cpp.obj


# Object files for target Snake
Snake_OBJECTS = \
"CMakeFiles/Snake.dir/main.cpp.obj"

# External object files for target Snake
Snake_EXTERNAL_OBJECTS =

Snake.exe: CMakeFiles/Snake.dir/main.cpp.obj
Snake.exe: CMakeFiles/Snake.dir/build.make
Snake.exe: W:/Programs/Programming\ environment/Librares/SFML-2.4.2/lib/libsfml-graphics-s-d.a
Snake.exe: W:/Programs/Programming\ environment/Librares/SFML-2.4.2/lib/libsfml-network-s-d.a
Snake.exe: W:/Programs/Programming\ environment/Librares/SFML-2.4.2/lib/libsfml-audio-s-d.a
Snake.exe: W:/Programs/Programming\ environment/Librares/SFML-2.4.2/lib/libsfml-window-s-d.a
Snake.exe: W:/Programs/Programming\ environment/Librares/SFML-2.4.2/lib/libsfml-system-s-d.a
Snake.exe: W:/Programs/Programming\ environment/Librares/SFML-2.4.2/lib/libfreetype.a
Snake.exe: W:/Programs/Programming\ environment/Librares/SFML-2.4.2/lib/libjpeg.a
Snake.exe: W:/Programs/Programming\ environment/Librares/SFML-2.4.2/lib/libopenal32.a
Snake.exe: W:/Programs/Programming\ environment/Librares/SFML-2.4.2/lib/libFLAC.a
Snake.exe: W:/Programs/Programming\ environment/Librares/SFML-2.4.2/lib/libvorbisenc.a
Snake.exe: W:/Programs/Programming\ environment/Librares/SFML-2.4.2/lib/libvorbisfile.a
Snake.exe: W:/Programs/Programming\ environment/Librares/SFML-2.4.2/lib/libvorbis.a
Snake.exe: W:/Programs/Programming\ environment/Librares/SFML-2.4.2/lib/libogg.a
Snake.exe: W:/Programs/Programming\ environment/Librares/SFML-2.4.2/lib/libopenal32.a
Snake.exe: W:/Programs/Programming\ environment/Librares/SFML-2.4.2/lib/libFLAC.a
Snake.exe: W:/Programs/Programming\ environment/Librares/SFML-2.4.2/lib/libvorbisenc.a
Snake.exe: W:/Programs/Programming\ environment/Librares/SFML-2.4.2/lib/libvorbisfile.a
Snake.exe: W:/Programs/Programming\ environment/Librares/SFML-2.4.2/lib/libvorbis.a
Snake.exe: W:/Programs/Programming\ environment/Librares/SFML-2.4.2/lib/libogg.a
Snake.exe: CMakeFiles/Snake.dir/linklibs.rsp
Snake.exe: CMakeFiles/Snake.dir/objects1.rsp
Snake.exe: CMakeFiles/Snake.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="W:\Programs\Programming environment\Projects\Fun\Snake\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Snake.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Snake.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Snake.dir/build: Snake.exe

.PHONY : CMakeFiles/Snake.dir/build

CMakeFiles/Snake.dir/requires: CMakeFiles/Snake.dir/main.cpp.obj.requires

.PHONY : CMakeFiles/Snake.dir/requires

CMakeFiles/Snake.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Snake.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Snake.dir/clean

CMakeFiles/Snake.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "W:\Programs\Programming environment\Projects\Fun\Snake" "W:\Programs\Programming environment\Projects\Fun\Snake" "W:\Programs\Programming environment\Projects\Fun\Snake\cmake-build-debug" "W:\Programs\Programming environment\Projects\Fun\Snake\cmake-build-debug" "W:\Programs\Programming environment\Projects\Fun\Snake\cmake-build-debug\CMakeFiles\Snake.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Snake.dir/depend

