cmake_minimum_required(VERSION 3.20)
project(avltree C)
set(CMAKE_C_STANDARD 99)
add_subdirectory(avl)
add_executable(avltree main.c)
target_link_libraries(avltree PUBLIC avl)

