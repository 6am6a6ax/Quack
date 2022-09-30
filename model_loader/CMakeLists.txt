cmake_minimum_required(VERSION 3.22)

project(model_loader)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(deps/imgui) 

include_directories(../engine/include)

set(SOURCES
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})