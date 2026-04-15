cmake_minimum_required(VERSION 4.2)
project(fadfs_cli C)

# 1. Configuration du prefix (Standard Arch local)
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/.local" CACHE PATH "..." FORCE)
endif()

# 2. Localisation des packages
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_INSTALL_PREFIX}")

find_package(xstdlib REQUIRED)
find_package(fadfs_core REQUIRED)

set(CMAKE_C_STANDARD 11)

add_executable(fasdfs_cli main.c)

target_link_libraries(fasdfs_cli PRIVATE
        fadfs_core::fadfs_core
        xstdlib::xstdlib
)

install(TARGETS fasdfs_cli
        RUNTIME DESTINATION bin
)