cmake_minimum_required(VERSION 3.20)

project(HateEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 REQUIRED)

add_executable(HateEngine
    src/main.cpp
    glad/src/glad.c
    src/Window.cpp
    src/Shader.cpp
    src/VAO.cpp
    src/VBO.cpp
    src/EBO.cpp
)

target_include_directories(HateEngine PRIVATE
    include
    glad/include
)

target_link_libraries(HateEngine PRIVATE
    glfw
)