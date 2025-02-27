cmake_minimum_required(VERSION 3.10)
project(rotating_cube)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

include(FetchContent)
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG        0.9.9.8
)
FetchContent_MakeAvailable(glm)

add_executable(rotating_cube
    src/main.cpp
    src/Window.cpp
)

target_include_directories(rotating_cube
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../include  # 프로젝트 루트의 include/ 경로
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${glm_SOURCE_DIR}                          # GLM 헤더(필요하다면)
)

target_link_libraries(rotating_cube
    SDL2::SDL2
)

