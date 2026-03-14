cmake_minimum_required(VERSION 3.16)

project(Tablero LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Tablero tablero.cpp
    tablero.h)

include(GNUInstallDirs)
install(TARGETS Tablero
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
