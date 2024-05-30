cmake_minimum_required(VERSION 3.28)
project(RayCast3DProject C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake-module)

set(SDL2_PATH "C:/Users/Mathi/Downloads/SDL2-devel-2.30.3-mingw/SDL2-2.30.3/x86_64-w64-mingw32")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(RayCast3DProject main.c
        SDLWindow.c
        SDLWindow.h
        Player.c
        Player.h)

target_link_libraries(RayCast3DProject ${SDL2_LIBRARY})