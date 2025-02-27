cmake_minimum_required(VERSION 3.10)
project(SoftwareRasterizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# 실행 파일 생성
add_executable(SoftwareRasterizer
    src/main.cpp
    src/math/Matrix4x4.cpp
	src/math/Quaternion.cpp
	src/math/Vector3.cpp
	src/math/Vector4.cpp
    src/window/Window.cpp
)

# SDL2 라이브러리 링크
target_link_libraries(SoftwareRasterizer ${SDL2_LIBRARIES})

# include 폴더 추가
target_include_directories(SoftwareRasterizer
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)
