cmake_minimum_required(VERSION 3.13)
project(ecs_150_project_1)

set(CMAKE_CXX_STANDARD 14)
set(GPP_ENABLE_WARNINGS "-O0 -Wall -Wno-unused-result")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GPP_ENABLE_WARNINGS}")
add_executable(ecs_150_project_1 main.cpp)