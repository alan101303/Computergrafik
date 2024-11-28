cmake_minimum_required(VERSION 3.14)

project(ProceduralPlayground
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


add_library(render_shared STATIC
    src/utils/vec.cpp
    src/render/shader.cpp
    src/render/Mesh.cpp
    src/render/StaticMeshActor.cpp
    src/render/glfw_window.cpp
    src/render/MeshViewer.cpp
    src/render/ShaderViewer.cpp
)

target_link_libraries(render_shared PUBLIC glfw lodePNG::lodePNG glew::glew OpenGL::GL)
target_compile_definitions(render_shared PUBLIC
    "$<$<CXX_COMPILER_ID:MSVC>:NOMINMAX>"
    "$<$<CXX_COMPILER_ID:MSVC>:_USE_MATH_DEFINES>"
    )
set(SHADER_PATH ${CMAKE_SOURCE_DIR}/src/shaders CACHE PATH "location of shader programs")
target_compile_definitions(render_shared PUBLIC "SHADER_PATH=\"${SHADER_PATH}\"")

add_executable(shvi src/main_shader_viewer.cpp)
target_link_libraries(shvi render_shared)

add_executable(terrain src/main_terrain.cpp)
target_link_libraries(terrain render_shared)

