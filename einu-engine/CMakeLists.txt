cmake_minimum_required(VERSION 3.14)

option(einu-engine_build_tests "Build all of EINU Engine's own tests." OFF)

option(einu-engine_build_examples "Build all of EINU Engine's own examples." OFF)

project(
  einu-engine
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

if(einu-engine_build_tests)
  enable_testing()
  set(fetch_googletest ON)
  set(core_build_tests ON)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(core)
add_subdirectory(window)
add_subdirectory(graphics)
add_subdirectory(extern)

if(einu-engine_build_examples)
  add_subdirectory(examples)
endif()