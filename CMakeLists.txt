cmake_minimum_required(VERSION 3.26)
project(opengl_learn C)

set(CMAKE_C_STANDARD 11)

add_executable(opengl_learn main.c)

add_subdirectory(deps/glfw)
add_subdirectory(deps/glad)
add_subdirectory(deps/shaderlib)

target_link_libraries(opengl_learn PUBLIC glfw glad shaderlib)
target_include_directories(opengl_learn PUBLIC
        "${PROJECT_BINARY_DIR}/deps/glfw/include"
        "${PROJECT_BINARY_DIR}/deps/glad/include"
        "${PROJECT_BINARY_DIR}/deps/shaderlib/include"
)

configure_file(
        shaders/shader.vs
        shaders/shader.vs
        COPYONLY
)
configure_file(
        shaders/shader.fs
        shaders/shader.fs
        COPYONLY
)
