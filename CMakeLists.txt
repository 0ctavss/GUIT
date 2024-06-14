cmake_minimum_required(VERSION 3.28)
project(GUIT)

set(CMAKE_CXX_STANDARD 17)

# Indica la ruta donde está instalado CURL
set(CURL_INCLUDE_DIR "C:/Users/MSI/CLionProjects/curl-8.8.0_2-win64-mingw/include")
set(CURL_LIBRARY "C:/Users/MSI/CLionProjects/curl-8.8.0_2-win64-mingw/lib/libcurl.dll.a")

# Añadir las rutas de inclusión y de las bibliotecas
include_directories(${CURL_INCLUDE_DIR})
link_directories("C:/Users/MSI/CLionProjects/curl-8.8.0_2-win64-mingw/lib")

# Añadir ejecutable
add_executable(GUIT main.cpp
        initRepo.cpp
        initRepo.h
        addFile.cpp
        addFile.h
        doCommit.cpp
        doCommit.h
        showHelp.h
        showHelp.cpp
)

# Vincular las bibliotecas necesarias
target_link_libraries(GUIT ${CURL_LIBRARY} ws2_32 wldap32)
