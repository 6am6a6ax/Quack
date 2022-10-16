cmake_minimum_required(VERSION 3.22)

project(vulkan_debugger)

set(CMAKE_CXX_STANDARD 14)

if (NOT TARGET engine)
    add_subdirectory(deps/engine)
endif()

add_executable(${PROJECT_NAME} /
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    /
    ${CMAKE_CURRENT_SOURCE_DIR}/src/layer.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE engine)