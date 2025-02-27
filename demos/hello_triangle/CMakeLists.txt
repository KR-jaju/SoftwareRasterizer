cmake_minimum_required(VERSION 3.10)
project(hello_triangle)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(hello_triangle
    src/main.cpp
    src/Window.cpp
)

target_include_directories(hello_triangle
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../include  # 프로젝트 루트의 include/ 경로
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(hello_triangle
    SDL2::SDL2
)

