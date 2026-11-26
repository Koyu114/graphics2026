cmake_minimum_required(VERSION 3.16)
project(OpenGLProject)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(OpenGLProject main.cpp)
target_link_libraries(OpenGLProject PRIVATE glfw OpenGL::GL)