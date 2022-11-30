cmake_minimum_required(VERSION 3.22)

project(engine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(OpenGL_GL_PREFERENCE GLVND)

if (NOT TARGET glfw)
        add_subdirectory(deps/glfw)
endif()

if (NOT TARGET imgui)
        add_subdirectory(deps/imgui)
endif()

if (NOT TARGET glew)
        add_subdirectory(deps/glew/build/cmake)
endif()

if (NOT TARGET glm)
        add_subdirectory(deps/glm)
endif()

if (NOT TARGET EnTT)
        add_subdirectory(deps/entt)
endif()

if (NOT TARGET yaml-cpp)
        add_subdirectory(deps/yaml-cpp)
endif()

if (NOT TARGET stb)
        add_subdirectory(deps/stb)
endif()

if (NOT TARGET assimp)
        add_subdirectory(deps/assimp)
endif()

# if (NOT TARGET spdlog)
#         add_subdirectory(deps/spdlog)
# endif()


#add_compile_definitions(STB_IMAGE_IMPLEMENTATION)
        
add_library(${PROJECT_NAME} STATIC /
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/application.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/asset_library.cpp
        /
        ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/gpu_buffer.cpp
        /
        ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/glfw/window_glfw.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/imgui/layer_imgui.cpp
        /
        ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/opengl/gpu_device_opengl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/opengl/gpu_buffer_opengl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/opengl/gpu_shader_opengl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/opengl/gpu_context_opengl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/opengl/gpu_texture_opengl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/opengl/gpu_framebuffer_opengl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/opengl/gpu_vertex_array_opengl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/opengl/gpu_shader_program_opengl.cpp
        /
        ${CMAKE_CURRENT_SOURCE_DIR}/src/render/ortographic_camera.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/render/renderer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/render/light.cpp
        /
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scene/scene.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scene/scene_serializer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scene/model.cpp
)

target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/quack/quack.h)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/deps/stb/)

target_link_libraries(${PROJECT_NAME} PUBLIC glm)
target_link_libraries(${PROJECT_NAME} PUBLIC glew)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC EnTT)
target_link_libraries(${PROJECT_NAME} PUBLIC imgui)
target_link_libraries(${PROJECT_NAME} PUBLIC assimp)
target_link_libraries(${PROJECT_NAME} PUBLIC yaml-cpp)
# target_link_libraries(${PROJECT_NAME} PUBLIC ImGuizmo)
# target_link_libraries(${PROJECT_NAME} PUBLIC spdlog)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})