cmake_minimum_required(VERSION 3.22)

project(ImGuizmo)

if (NOT TARGET imgui)
    add_subdirectory(deps/imgui)
endif()

include_directories(deps/imgui)

add_library(${PROJECT_NAME} STATIC /
    ${CMAKE_CURRENT_SOURCE_DIR}/ImGuizmo.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})