option(EINU_FETCH_GOOGLETEST OFF)
option(EINU_FETCH_EASY_PROFILER OFF)

include(FetchContent)

FetchContent_Declare(
  bitplusplus
  GIT_REPOSITORY https://github.com/xiaoyuechen/bitplusplus.git
  GIT_TAG v0.1.1)
FetchContent_MakeAvailable(bitplusplus)

if(EINU_FETCH_GOOGLETEST)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.10.0)

  set(INSTALL_GTEST
      OFF
      CACHE BOOL "" FORCE)

  if(MSVC)
    # cmake-lint: disable=C0103
    set(gtest_force_shared_crt
        ON
        CACHE BOOL "" FORCE)
  endif()

  FetchContent_MakeAvailable(googletest)

  set_target_properties(gtest gtest_main gmock gmock_main
                        PROPERTIES FOLDER "googletest")
endif()

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3.2)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 0.9.9.8)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
  abseil-cpp
  GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
  GIT_TAG 20200923.2)
FetchContent_MakeAvailable(abseil-cpp)

add_subdirectory(glad)

add_subdirectory(stb)

# FetchContent_Declare( assimp GIT_REPOSITORY
# https://github.com/assimp/assimp.git GIT_TAG        v5.0.1 )
#
# set(ASSIMP_BUILD_TESTS OFF)
#
# FetchContent_MakeAvailable(assimp)

if(EINU_FETCH_EASY_PROFILER)
  FetchContent_Declare(
    easy-profiler
    GIT_REPOSITORY https://github.com/yse/easy_profiler.git
    GIT_TAG v2.1.0)
  set(EASY_PROFILER_NO_GUI ON)
  FetchContent_MakeAvailable(easy-profiler)
endif()
