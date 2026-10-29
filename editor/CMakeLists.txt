cmake_minimum_required(VERSION 3.20)

project(Editor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(Editor
    main.cpp
)

target_link_libraries(Editor PRIVATE HateEngine)