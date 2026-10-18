cmake_minimum_required(VERSION 3.20)

project(HateEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 REQUIRED)

add_executable(HateEngine
    src/main.cpp
    external/src/glad.c
    src/Window.cpp
    src/Shader.cpp
    src/VAO.cpp
    src/VBO.cpp
    src/EBO.cpp
    src/Texture.cpp
)

target_include_directories(HateEngine PRIVATE
    include
    external/include
)

target_link_libraries(HateEngine PRIVATE
    glfw
)
