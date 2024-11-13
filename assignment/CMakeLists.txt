cmake_minimum_required(VERSION 3.14)

project(LindenmayerSystems
    VERSION 1.0
    LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 17)

# set output paths
set(PROJECT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

# default to Release builds
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()

find_package(OpenGL REQUIRED)
add_subdirectory(lib/glew)
add_subdirectory(lib/glfw)
add_subdirectory(lib/lodePNG)


add_executable(lsys
	src/lsystem.cpp
	src/lsystem_load.cpp
	src/main.cpp
	src/utils/misc.cpp
	src/utils/vec.cpp
	src/utils/render_2d.cpp
	src/utils/render_svg.cpp
	src/utils/LSystemViewer.cpp
	src/utils/glfw_window.cpp
	src/utils/glmath.cpp
	src/utils/shader.cpp
	lib/Jzon/Jzon.cpp
)

target_compile_definitions(lsys PUBLIC -DGLEW_STATIC)
target_link_libraries(lsys PUBLIC glfw lodePNG::lodePNG glew::glew OpenGL::GL)

# JSON
target_include_directories(lsys PUBLIC "${CMAKE_SOURCE_DIR}/lib/Jzon")

################################################################################
# OpenGL paths to shaders
################################################################################

set(SHADER_PATH	 ${CMAKE_SOURCE_DIR}/shaders			CACHE PATH "location of shader programs")
add_definitions("-DSHADER_PATH=\"${SHADER_PATH}\"")
