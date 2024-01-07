cmake_minimum_required(VERSION 3.25)

project(shaderlib LANGUAGES C)

add_subdirectory(src)

target_include_directories(shaderlib PUBLIC include)