cmake_minimum_required(VERSION 3.22)

project(editor)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(deps/engine)
add_subdirectory(deps/ImGuizmo)

include_directories(include)
#include_directories(deps/imgui)
include_directories(deps/ImGuizmo)

include_directories(deps/engine/include)

set(SOURCES
    src/main.cpp
    /
    src/layers/layer_quad.cpp
    src/layers/layer_triangle.cpp
    src/layers/layer_hierarchy_panel.cpp
    src/layers/layer_components.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE engine)
target_link_libraries(${PROJECT_NAME} PRIVATE ImGuizmo)
