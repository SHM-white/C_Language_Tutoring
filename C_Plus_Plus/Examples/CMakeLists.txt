cmake_minimum_required(VERSION 3.10)

project(C_Plus_Plus_Examples)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_FILES main.cpp test.cpp)

add_executable(Example ${SOURCE_FILES})


