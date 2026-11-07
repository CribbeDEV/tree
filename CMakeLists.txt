cmake_minimum_required(VERSION 3.10)

project(tree LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(tree tree.c)

target_compile_options(tree PRIVATE -Wall -Wextra)

install(TARGETS tree DESTINATION bin)
