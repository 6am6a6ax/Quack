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
add_subdirectory(vendor/glm)
#add_subdirectory(vendor/stb)

include_directories(include)
include_directories(vendor/imgui)
#include_directories(vendor/glm)
include_directories(vendor/stb)

set(SOURCES
        src/core/application.cpp
        src/core/application_description.cpp
        src/core/window.cpp
        src/core/window_description.cpp
        /
        src/graphics/gpu_buffer.cpp
        /
        src/platform/glfw/window_glfw.cpp
        /
        src/platform/imgui/layer_imgui.cpp
        /
        src/platform/opengl/gpu_context_opengl.cpp
        src/platform/opengl/gpu_buffer_opengl.cpp
        src/platform/opengl/gpu_device_opengl.cpp
        src/platform/opengl/gpu_shader_opengl.cpp
        src/platform/opengl/gpu_shader_program_opengl.cpp
        src/platform/opengl/gpu_vertex_array_opengl.cpp
        src/platform/opengl/gpu_texture_opengl.cpp
        /
        src/render/ortographic_camera.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glew)
target_link_libraries(${PROJECT_NAME} imgui)
target_link_libraries(${PROJECT_NAME} glm)
#target_link_libraries(${PROJECT_NAME} stb)