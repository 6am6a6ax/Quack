cmake_minimum_required(VERSION 3.22)

project(quack)

add_subdirectory(engine)
add_subdirectory(editor)

target_link_libraries(editor PUBLIC engine)