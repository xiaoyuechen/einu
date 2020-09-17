cmake_minimum_required(VERSION 3.14)

project(ecs-engine VERSION 0.5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(ecs-engine)
add_subdirectory(tests)
add_subdirectory(extern)