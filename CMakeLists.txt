cmake_minimum_required(VERSION 3.22)
project(engine)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glew/build/cmake)


#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)
#
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#
#find_package(Qt5 COMPONENTS Core REQUIRED)
#find_package(Qt5 COMPONENTS Widgets REQUIRED)

#set(HEADERS
#        ${CMAKE_CURRENT_SOURCE_DIR}/gpu_adapter.hpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/gpu_buffer.hpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/gpu_buffer_description.hpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/gpu_buffer_utility.hpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/gpu_context.hpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/gpu_device.hpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/gpu_pipeline_state.hpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/gpu_pipeline_state_description.hpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/gpu_pipeline_state_element.hpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/gpu_pipeline_state_layout.hpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/gpu_pixel_format.hpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/gpu_resource.hpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/gpu_resource_usage.hpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/gpu_shader.hpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/gpu_shader_description.hpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/gpu_shader_program.hpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/gpu_shader_program_description.hpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/gpu_shader_program_stage.hpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/gpu_texture.hpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/gpu_texture_description.hpp
#)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(engine src/main.cpp)

target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glew)

#target_link_libraries(engine
#        Qt5::Core
#        Qt5::Widgets)