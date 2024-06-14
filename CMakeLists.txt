set(OPENSSL_INCLUDE_DIR "C:/Program Files/OpenSSL-Win64/include")
set(OPENSSL_LIB_DIR "C:/Program Files/OpenSSL-Win64/lib/VC/x64/MD")

include_directories(${OPENSSL_INCLUDE_DIR})
link_directories(${OPENSSL_LIB_DIR})

# Añadir ejecutable
add_executable(untitled main.cpp
        client.hpp
        server.hpp
        utils.hpp
        server.cpp
        client.cpp
        utils.cpp)

# Vincular las bibliotecas necesarias
target_link_libraries(untitled ${OPENSSL_LIB_DIR}/libcrypto.lib ${OPENSSL_LIB_DIR}/libssl.lib)