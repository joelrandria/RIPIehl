cmake_minimum_required(VERSION 3.3)
project(RIPIehl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Mat4.h Vec2.h Vec3.h Vec4.h)
add_executable(RIPIehl ${SOURCE_FILES})