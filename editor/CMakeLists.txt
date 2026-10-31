cmake_minimum_required(VERSION 3.20)

project(editor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(editor
    main.cpp
)

target_link_libraries(editor PRIVATE HateEngine)