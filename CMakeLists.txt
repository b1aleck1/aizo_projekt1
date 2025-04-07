cmake_minimum_required(VERSION 3.29)
project(projekt)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(projekt
        program/src/main.cpp
        program/src/Konfiguracja.cpp
        program/src/Generowanie.h
        program/src/ObslugaWynikow.h
        program/src/ObslugaPlikow.h
        program/src/Aplikacja.h
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)