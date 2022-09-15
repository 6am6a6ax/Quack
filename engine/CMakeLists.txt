cmake_minimum_required(VERSION 3.22)

project(engine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/glew/build/cmake)

include_directories(include)
include_directories(vendor/imgui)

set(SOURCES
        src/application.cpp
        src/gpu_buffer.cpp
        src/gpu_context.cpp
        src/window_glfw.cpp
        src/application_description.cpp
        src/window.cpp
        src/window_description.cpp
        src/layer_imgui.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glew)
target_link_libraries(${PROJECT_NAME} imgui)