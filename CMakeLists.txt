cmake_minimum_required(VERSION 3.14)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    set(ECS_STANDALONE TRUE)
endif()

option(ECS_BUILD_TESTS "Build all of ecs-engine's own tests." ${ANT_STANDALONE})

project(ecs-engine VERSION 0.5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(ecs-engine)
add_subdirectory(extern)

if(ecs_build_tests)
  enable_testing()
  add_subdirectory(tests)
endif()