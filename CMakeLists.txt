cmake_minimum_required(VERSION 3.28)
project(untitled)

set(CMAKE_CXX_STANDARD 26)
# Configurar la ruta de inclusión de OpenSSL
set(CMAKE_INCLUDE_PATH "C:/Program Files/OpenSSL-Win64/include")
add_executable(untitled main.cpp
        client.hpp
        server.hpp
        utils.hpp
        server.cpp
        client.cpp
        utils.cpp)
