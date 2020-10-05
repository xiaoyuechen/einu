cmake_minimum_required(VERSION 3.14)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    set(EINU_STANDALONE TRUE)
endif()

option(EINU_BUILD_TESTS "Build all of einu-engine's own tests." ${EINU_STANDALONE})

project(einu-engine VERSION 0.5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(einu-engine)
add_subdirectory(extern)

if(EINU_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()