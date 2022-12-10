cmake_minimum_required(VERSION 3.22)

project(editor)

set(CMAKE_CXX_STANDARD 14)

if (NOT TARGET engine)
    add_subdirectory(deps/engine)
endif()

if (NOT TARGET ImGuizmo)
    add_subdirectory(deps/imguizmo)
endif()

add_executable(${PROJECT_NAME} /
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/camera.cpp
    /
    ${CMAKE_CURRENT_SOURCE_DIR}/src/layers/layer_quad.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE engine)
target_link_libraries(${PROJECT_NAME} PRIVATE ImGuizmo)
