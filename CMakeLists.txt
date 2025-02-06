cmake_minimum_required(VERSION 3.0.0)
project(learn_opengl VERSION 0.1.0)

add_executable(learn_opengl src/main.cpp)

target_link_libraries(learn_opengl glfw)