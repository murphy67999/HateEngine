cmake_minimum_required(VERSION 3.20)

project(HateEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 REQUIRED)

add_executable(HateEngine
    src/main.cpp
    external/glad/src/glad.c
    src/Window.cpp
    src/Shader.cpp
    src/Texture.cpp
    src/Input.cpp
    src/Camera.cpp
    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
    src/Mesh.cpp
    external/imgui/misc/cpp/imgui_stdlib.cpp
)

target_include_directories(HateEngine PRIVATE
    include/
    external/
    external/glad/include/
    external/glm/
    external/imgui/
)

target_link_libraries(HateEngine PRIVATE
    glfw
)
