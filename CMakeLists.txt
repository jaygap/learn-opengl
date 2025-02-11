cmake_minimum_required(VERSION 3.10.0)
project(learn_opengl VERSION 0.1.0)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED) 

add_executable(learn_opengl 
    src/main.cpp
    src/glad.c
    include/glad/glad.h
    include/shader.h
    include/stb_image.h
)

include_directories(include)

target_link_libraries(learn_opengl 
    glfw
    OpenGL::GL
)