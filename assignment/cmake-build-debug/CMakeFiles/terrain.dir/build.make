# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.29

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2024.2.2\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2024.2.2\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Utente\Desktop\Magistrale\FallSemester2024\Computer_Graphics\Computergrafik-assignment_9

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Utente\Desktop\Magistrale\FallSemester2024\Computer_Graphics\Computergrafik-assignment_9\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/terrain.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/terrain.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/terrain.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/terrain.dir/flags.make

CMakeFiles/terrain.dir/src/main_terrain.cpp.obj: CMakeFiles/terrain.dir/flags.make
CMakeFiles/terrain.dir/src/main_terrain.cpp.obj: CMakeFiles/terrain.dir/includes_CXX.rsp
CMakeFiles/terrain.dir/src/main_terrain.cpp.obj: C:/Users/Utente/Desktop/Magistrale/FallSemester2024/Computer_Graphics/Computergrafik-assignment_9/src/main_terrain.cpp
CMakeFiles/terrain.dir/src/main_terrain.cpp.obj: CMakeFiles/terrain.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Utente\Desktop\Magistrale\FallSemester2024\Computer_Graphics\Computergrafik-assignment_9\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/terrain.dir/src/main_terrain.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/terrain.dir/src/main_terrain.cpp.obj -MF CMakeFiles\terrain.dir\src\main_terrain.cpp.obj.d -o CMakeFiles\terrain.dir\src\main_terrain.cpp.obj -c C:\Users\Utente\Desktop\Magistrale\FallSemester2024\Computer_Graphics\Computergrafik-assignment_9\src\main_terrain.cpp

CMakeFiles/terrain.dir/src/main_terrain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/terrain.dir/src/main_terrain.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Utente\Desktop\Magistrale\FallSemester2024\Computer_Graphics\Computergrafik-assignment_9\src\main_terrain.cpp > CMakeFiles\terrain.dir\src\main_terrain.cpp.i

CMakeFiles/terrain.dir/src/main_terrain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/terrain.dir/src/main_terrain.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Utente\Desktop\Magistrale\FallSemester2024\Computer_Graphics\Computergrafik-assignment_9\src\main_terrain.cpp -o CMakeFiles\terrain.dir\src\main_terrain.cpp.s

# Object files for target terrain
terrain_OBJECTS = \
"CMakeFiles/terrain.dir/src/main_terrain.cpp.obj"

# External object files for target terrain
terrain_EXTERNAL_OBJECTS =

terrain.exe: CMakeFiles/terrain.dir/src/main_terrain.cpp.obj
terrain.exe: CMakeFiles/terrain.dir/build.make
terrain.exe: librender_shared.a
terrain.exe: libglfw3.a
terrain.exe: liblodePNG.a
terrain.exe: libglew.a
terrain.exe: CMakeFiles/terrain.dir/linkLibs.rsp
terrain.exe: CMakeFiles/terrain.dir/objects1.rsp
terrain.exe: CMakeFiles/terrain.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\Utente\Desktop\Magistrale\FallSemester2024\Computer_Graphics\Computergrafik-assignment_9\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable terrain.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\terrain.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/terrain.dir/build: terrain.exe
.PHONY : CMakeFiles/terrain.dir/build

CMakeFiles/terrain.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\terrain.dir\cmake_clean.cmake
.PHONY : CMakeFiles/terrain.dir/clean

CMakeFiles/terrain.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Utente\Desktop\Magistrale\FallSemester2024\Computer_Graphics\Computergrafik-assignment_9 C:\Users\Utente\Desktop\Magistrale\FallSemester2024\Computer_Graphics\Computergrafik-assignment_9 C:\Users\Utente\Desktop\Magistrale\FallSemester2024\Computer_Graphics\Computergrafik-assignment_9\cmake-build-debug C:\Users\Utente\Desktop\Magistrale\FallSemester2024\Computer_Graphics\Computergrafik-assignment_9\cmake-build-debug C:\Users\Utente\Desktop\Magistrale\FallSemester2024\Computer_Graphics\Computergrafik-assignment_9\cmake-build-debug\CMakeFiles\terrain.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/terrain.dir/depend
