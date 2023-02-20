cmake_minimum_required(VERSION 3.24)

project(triangle)
project(cube)
project(cube_refactored)
project(cube_instancing)

set(CMAKE_CXX_STANDARD 17)
set(GRAPHICS3_UTILS_H Utils.h)
set(GRAPHICS3_UTILS_SRC Utils.cpp)

add_executable(triangle triangle.cpp)
add_executable(cube cube.cpp)
add_executable(cube_refactored CubeRefactored.cpp Utils.h Utils.cpp CubeRefactoredFragShader.glsl CubeRefactoredVertShader.glsl)
add_executable(cube_instancing CubeInstancing.cpp Utils.h Utils.cpp CubeInstancingFragShader.glsl CubeInstancingVertShader.glsl)

include_directories(
        include
        /usr/local/include
        /usr/local/lib
)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_library(SOIL2 soil2-debug)

target_link_libraries(triangle ${OPENGL_LIBRARIES} glfw)
target_link_libraries(triangle ${SOIL})
target_link_libraries(triangle GLEW::GLEW)

target_link_libraries(cube ${OPENGL_LIBRARIES} glfw)
target_link_libraries(cube ${SOIL})
target_link_libraries(cube GLEW::GLEW)

target_link_libraries(cube_refactored ${OPENGL_LIBRARIES} glfw)
target_link_libraries(cube_refactored ${SOIL})
target_link_libraries(cube_refactored GLEW::GLEW)

target_link_libraries(cube_instancing ${OPENGL_LIBRARIES} glfw)
target_link_libraries(cube_instancing ${SOIL})
target_link_libraries(cube_instancing GLEW::GLEW)