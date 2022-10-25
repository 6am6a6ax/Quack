cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 17)
project(vulkan_demo)

if (NOT TARGET glfw)
    add_subdirectory(deps/glfw)
endif()

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC -lvulkan)

file(COPY shaders DESTINATION ${CMAKE_BINARY_DIR})