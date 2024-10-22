Semester Overview
=================
1. [x] Raytracing
2. [ ] Rasterization and OpenGL
3. [ ] Procedural Techniques
4. [ ] Modeling

Ray Tracer
==========

We are using a couple of modern C++ features, so please ensure that you use a recent C++ compiler (GCC 8, Clang 7, Visual Studio 2017 are tested).
You will need [CMake](https://www.cmake.org) for setting up the build environment.


Building with QtCreator or CLion (supported on Linux/MacOS/Windows)
-------------------------------------------------------------------

It should be sufficient to open the CMakeLists.txt as a project, then using the
build button.

Building under the commandline
------------------------------

On Linux and MacOS, you can use a regular terminal.
On Windows, this works best inside a WSL (Windows Subsystem for Linux) environment.

Inside the exercise's top-level directory, execute the following commands:

    mkdir build
    cd build
    cmake ..
    make

The last command -- i.e. `make` -- compiles the application. Rerun it whenever you have added/changed code in order to recompile.
You can use `make -j8` to compile with 8 cores (choose an appropriate number).

To build a pretty documentation use:

    make doc

and open the `index.html` in the html folder with your favourite browser. To build the documentation, you must install Doxygen.


Building with XCode (macOS)
---------------------------

If you wish, you can use the CMake build system to generate an XCode project.
Inside the exercise's top-level directory, execute the following commands:

    mkdir xcode
    cd xcode
    cmake -G Xcode ..
    open RayTracing.xcodeproj

Optionally, this project uses OpenMP for parallelization. Unfortunately,
XCode's compiler (based on clang) does not come with OpenMP by default.
You can install it from homebrew using `brew install libomp`.
Then set this environment variable
    export OpenMP_ROOT=/opt/homebrew/opt/libomp/
before running cmake (or delete your build folder and run it again).


Building under Microsoft Windows (Visual Studio)
------------------------------------------------

New way:

* Open the CMakeLists.txt as project
* Hopefully you can just click 'build'

Old way:

* Start the CMake-GUI.
* Open the top-level project directory (`assignment_0*`) as source directory.
* Create and select a subfolder "build" of the raytracing folder as *build directory*
* Click on configure and select Visual Studio as generator.
* Click generate to create the Visual Studio project files.
* Open the Visual Studio solution file that is in the build directory you chose in CMake.


Running the Ray Tracer (commandline)
-------------------------------------

The program expects two command line arguments:
 - a path two an input scene (`*.sce`) and
 - a path to an output image (`*.tga`).

To render the scene with the three spheres, while inside the `build` directory, type in your shell:

    ./raytrace ../scenes/spheres/spheres.sce output.tga

If you have finished all exercise tasks, use

    ./raytrace 0

to render all scenes at once.

On Windows, this would be

    .\raytrace.exe ../scenes/spheres/spheres.sce output.tga


You may have to adjust the relative paths if the build folder
containing the `raytrace` or `raytrace.exe` binary is not a
direct subfolder of the project folder.

Make sure (e.g. with `ls`) that you are specifing the correct path to the input file.
The output file will be saved in the current working directory of the program, i.e. the directory you started it from.

If `raytrace 0` does not find the input files, you may have to adjust them in `raytrace.cpp`.


Running the Ray Tracer from IDEs
-------------------------------------

To set the command line parameters in IDEs like MSVC or Xcode, please refer to the documentation of these programs (or use the command line...).
You'll likely have to set which program should be run (`raytrace`), a working directory, and commandline arguments.
If you set the working directory to the build folder, the above paths should work just the same.


