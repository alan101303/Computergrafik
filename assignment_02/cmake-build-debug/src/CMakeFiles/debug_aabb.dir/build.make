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
CMAKE_SOURCE_DIR = "C:\Users\Richie\Documents\Uni Bern\Computergrafik\Computergrafik\assignment_01"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Richie\Documents\Uni Bern\Computergrafik\Computergrafik\assignment_01\cmake-build-debug"

# Include any dependencies generated for this target.
include src/CMakeFiles/debug_aabb.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/debug_aabb.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/debug_aabb.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/debug_aabb.dir/flags.make

src/CMakeFiles/debug_aabb.dir/debug_aabb.cpp.obj: src/CMakeFiles/debug_aabb.dir/flags.make
src/CMakeFiles/debug_aabb.dir/debug_aabb.cpp.obj: C:/Users/Richie/Documents/Uni\ Bern/Computergrafik/Computergrafik/assignment_01/src/debug_aabb.cpp
src/CMakeFiles/debug_aabb.dir/debug_aabb.cpp.obj: src/CMakeFiles/debug_aabb.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\Richie\Documents\Uni Bern\Computergrafik\Computergrafik\assignment_01\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/debug_aabb.dir/debug_aabb.cpp.obj"
	cd /d C:\Users\Richie\DOCUME~1\UNIBER~1\COMPUT~1\COMPUT~1\ASSIGN~1\CMAKE-~1\src && C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/debug_aabb.dir/debug_aabb.cpp.obj -MF CMakeFiles\debug_aabb.dir\debug_aabb.cpp.obj.d -o CMakeFiles\debug_aabb.dir\debug_aabb.cpp.obj -c "C:\Users\Richie\Documents\Uni Bern\Computergrafik\Computergrafik\assignment_01\src\debug_aabb.cpp"

src/CMakeFiles/debug_aabb.dir/debug_aabb.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/debug_aabb.dir/debug_aabb.cpp.i"
	cd /d C:\Users\Richie\DOCUME~1\UNIBER~1\COMPUT~1\COMPUT~1\ASSIGN~1\CMAKE-~1\src && C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Richie\Documents\Uni Bern\Computergrafik\Computergrafik\assignment_01\src\debug_aabb.cpp" > CMakeFiles\debug_aabb.dir\debug_aabb.cpp.i

src/CMakeFiles/debug_aabb.dir/debug_aabb.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/debug_aabb.dir/debug_aabb.cpp.s"
	cd /d C:\Users\Richie\DOCUME~1\UNIBER~1\COMPUT~1\COMPUT~1\ASSIGN~1\CMAKE-~1\src && C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Richie\Documents\Uni Bern\Computergrafik\Computergrafik\assignment_01\src\debug_aabb.cpp" -o CMakeFiles\debug_aabb.dir\debug_aabb.cpp.s

# Object files for target debug_aabb
debug_aabb_OBJECTS = \
"CMakeFiles/debug_aabb.dir/debug_aabb.cpp.obj"

# External object files for target debug_aabb
debug_aabb_EXTERNAL_OBJECTS =

debug_aabb.exe: src/CMakeFiles/debug_aabb.dir/debug_aabb.cpp.obj
debug_aabb.exe: src/CMakeFiles/debug_aabb.dir/build.make
debug_aabb.exe: src/libcommon.a
debug_aabb.exe: src/CMakeFiles/debug_aabb.dir/linkLibs.rsp
debug_aabb.exe: src/CMakeFiles/debug_aabb.dir/objects1.rsp
debug_aabb.exe: src/CMakeFiles/debug_aabb.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="C:\Users\Richie\Documents\Uni Bern\Computergrafik\Computergrafik\assignment_01\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ..\debug_aabb.exe"
	cd /d C:\Users\Richie\DOCUME~1\UNIBER~1\COMPUT~1\COMPUT~1\ASSIGN~1\CMAKE-~1\src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\debug_aabb.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/debug_aabb.dir/build: debug_aabb.exe
.PHONY : src/CMakeFiles/debug_aabb.dir/build

src/CMakeFiles/debug_aabb.dir/clean:
	cd /d C:\Users\Richie\DOCUME~1\UNIBER~1\COMPUT~1\COMPUT~1\ASSIGN~1\CMAKE-~1\src && $(CMAKE_COMMAND) -P CMakeFiles\debug_aabb.dir\cmake_clean.cmake
.PHONY : src/CMakeFiles/debug_aabb.dir/clean

src/CMakeFiles/debug_aabb.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Richie\Documents\Uni Bern\Computergrafik\Computergrafik\assignment_01" "C:\Users\Richie\Documents\Uni Bern\Computergrafik\Computergrafik\assignment_01\src" "C:\Users\Richie\Documents\Uni Bern\Computergrafik\Computergrafik\assignment_01\cmake-build-debug" "C:\Users\Richie\Documents\Uni Bern\Computergrafik\Computergrafik\assignment_01\cmake-build-debug\src" "C:\Users\Richie\Documents\Uni Bern\Computergrafik\Computergrafik\assignment_01\cmake-build-debug\src\CMakeFiles\debug_aabb.dir\DependInfo.cmake" "--color=$(COLOR)"
.PHONY : src/CMakeFiles/debug_aabb.dir/depend

