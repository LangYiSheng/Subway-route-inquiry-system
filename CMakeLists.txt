cmake_minimum_required(VERSION 3.26)
project(Subway-route-inquiry-system)

set(CMAKE_CXX_STANDARD 14)
#[[set(CMAKE_EXE_LINKER_FLAGS "-static")]]
add_executable(Subway-route-inquiry-system
        main.cpp
        Line.h
        Line.cpp
        Transfer.cpp
        Transfer.h
        FileIO.cpp
        FileIO.h
)
