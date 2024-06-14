cmake_minimum_required(VERSION 3.27)
project(GUIT)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(GUIT
        comandos.cpp
        comandos.h
        main.cpp
        ServerConector.h
        ServerConector.cpp)
