cmake_minimum_required(VERSION 3.22)

project(model_loader)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(deps/engine)

add_executable(${PROJECT_NAME} /
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE engine)
target_link_libraries(${PROJECT_NAME} PRIVATE engine)