cmake_minimum_required(VERSION 3.25)
project(boundary_fill)

set(CMAKE_CXX_STANDARD 17)

add_executable(boundary_fill main.cpp olcPixelGameEngine.h)
target_link_libraries(boundary_fill X11 GL pthread png  "stdc++fs")
