cmake_minimum_required(VERSION 3.22)

project(editor)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(../engine/include)

set(SOURCES
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})