cmake_minimum_required(VERSION 3.20)

project(ligma LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(ligma
    main.cpp
)

target_link_libraries(ligma PRIVATE HateEngine)