cmake_minimum_required(VERSION 3.22)

project(engine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(OpenGL_GL_PREFERENCE GLVND)

#add_compile_definitions(STB_IMAGE_IMPLEMENTATION)

add_subdirectory(deps/glfw)
add_subdirectory(deps/imgui)
add_subdirectory(deps/glew/build/cmake)
add_subdirectory(deps/glm)
add_subdirectory(deps/entt)
add_subdirectory(deps/yaml-cpp)
add_subdirectory(deps/stb)
#add_subdirectory(deps/assimp)

include_directories(include)
include_directories(deps/imgui)
include_directories(deps/glm)
include_directories(deps/stb)
include_directories(deps/entt/src)
include_directories(deps/yaml-cpp/include)

#include_directories(deps/assimp/include)

set(SOURCES
        src/core/application.cpp
        src/core/window.cpp
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
        src/platform/opengl/gpu_framebuffer_opengl.cpp
        /
        src/render/ortographic_camera.cpp
        src/render/scene.cpp
        src/render/scene_serializer.cpp
)


add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_precompile_headers(${PROJECT_NAME} PUBLIC include/quack/quack.h)

target_include_directories(${PROJECT_NAME} PUBLIC deps/imgui)

#add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC glew)
target_link_libraries(${PROJECT_NAME} PUBLIC imgui)
target_link_libraries(${PROJECT_NAME} PUBLIC glm)
#target_link_libraries(${PROJECT_NAME} PUBLIC stb)
target_link_libraries(${PROJECT_NAME} PUBLIC EnTT)
target_link_libraries(${PROJECT_NAME} PUBLIC yaml-cpp)
#target_link_libraries(${PROJECT_NAME} PRIVATE assimp)
