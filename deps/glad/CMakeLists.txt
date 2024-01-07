cmake_minimum_required(VERSION 3.0...3.20 FATAL_ERROR)

project(glad VERSION 3.3.9 LANGUAGES C)

add_subdirectory(src)

target_include_directories(glad PUBLIC include)