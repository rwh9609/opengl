cmake_minimum_required(VERSION 3.24)
project(graphics)
project(graphics2)

set(CMAKE_CXX_STANDARD 17)

add_executable(graphics triangle.cpp)
add_executable(graphics2 cube.cpp)

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

target_link_libraries(graphics
        ${OPENGL_LIBRARIES} glfw
#        ${SOIL2}
        )

target_link_libraries(graphics ${SOIL})
target_link_libraries(graphics GLEW::GLEW)



target_link_libraries(graphics2
        ${OPENGL_LIBRARIES} glfw
        )
target_link_libraries(graphics2 ${SOIL})
target_link_libraries(graphics2 GLEW::GLEW)