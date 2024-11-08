# OpenGL & GLEW library
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

# Make sure the textures, shaders and meshes are available
set(SHADER_PATH   ${CMAKE_SOURCE_DIR}/shaders      CACHE PATH "location of shader programs")
set(TEXTURE_PATH  ${CMAKE_SOURCE_DIR}/textures     CACHE PATH "location of texture images")
set(MESH_PATH     ${CMAKE_SOURCE_DIR}/meshes       CACHE PATH "location of example meshes")
add_definitions("-DSHADER_PATH=\"${SHADER_PATH}\"")
add_definitions("-DMESH_PATH=\"${MESH_PATH}\"")
add_definitions("-DTEXTURE_PATH=\"${TEXTURE_PATH}\"")

# source files
set(SOURCES glfw_window.cpp glmath.cpp main.cpp shader.cpp ShadowViewer.cpp Mesh.cpp sphere.cpp)
set(HEADERS glfw_window.h gl.h glmath.h shader.h ShadowViewer.h Mesh.h sphere.h Quad.h CubeMapVisualization.h dumpOpenGLBuffer.h)
# executable
add_executable(ShadowViewer ${HEADERS} ${SOURCES})
target_link_libraries(ShadowViewer glfw lodePNG::lodePNG glew::glew OpenGL::GL)
target_include_directories(ShadowViewer SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
