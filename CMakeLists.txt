cmake_minimum_required(VERSION 3.14)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
  set(EINU_STANDALONE TRUE)
endif()

option(EINU_BUILD_TESTS "Build all of einu-engine's own tests." ${EINU_STANDALONE})

option(EINU_BUILD_EXAMPLES "Build all of einu-engine's own examples." ${EINU_STANDALONE})

project(
  einu-engine
  VERSION 0.5
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(MSVC)
  # /wd4005  macro-redefinition
  # /wd4068  unknown pragma
  # /wd4244  conversion from 'type1' to 'type2'
  # /wd4267  conversion from 'size_t' to 'type2'
  # /wd4800  force value to bool 'true' or 'false' (performance warning)
  # /wd4996  deprecated allocator
  add_compile_options(/wd4005 /wd4068 /wd4244 /wd4267 /wd4800 /wd4996)
  add_definitions(/DNOMINMAX /DWIN32_LEAN_AND_MEAN=1 /D_CRT_SECURE_NO_WARNINGS)
endif()

add_subdirectory(einu-engine)
add_subdirectory(extern)

if(EINU_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

if(EINU_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()