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

add_executable(fadfs_cli main.c
        src/repl.c
        include/repl.h
        src/test_cmd.c
        include/cmd_def.h)

target_link_libraries(fadfs_cli PRIVATE
        fadfs_core::fadfs_core
        xstdlib::xstdlib
)

install(TARGETS fadfs_cli
        RUNTIME DESTINATION bin
)