cmake_minimum_required(VERSION 3.22.1)

project(STACK)
include_directories(headers)
include_directories(src)

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} ./src/main.cpp )