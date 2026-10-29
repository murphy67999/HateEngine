cmake_minimum_required(VERSION 3.20)

project(sigma LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(sigma
    main.cpp
)

target_link_libraries(sigma PRIVATE HateEngine)