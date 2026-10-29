cmake_minimum_required(VERSION 3.20)

project(HateEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 REQUIRED)

add_library(HateEngine STATIC
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
    src/Project.cpp
    src/VertexArray.cpp
    src/Scene.cpp
    src/Engine.cpp
    src/Renderer.cpp
)

target_include_directories(HateEngine PUBLIC
    include/
    external/
    external/glad/include/
    external/glm/
    external/imgui/
)

target_link_libraries(HateEngine PUBLIC
    glfw
)

add_subdirectory(editor)
add_subdirectory(projects/sigma)
add_subdirectory(projects/ligma)