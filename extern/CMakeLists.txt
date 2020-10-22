include(FetchContent)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.3.2
)

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git 
  GIT_TAG        0.9.9.8
)

FetchContent_MakeAvailable(glm)

FetchContent_Declare(
  abseil-cpp
  GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
  GIT_TAG        20200923.2
)

FetchContent_MakeAvailable(abseil-cpp)

add_subdirectory(glad)



# FetchContent_Declare(
#   assimp
#   GIT_REPOSITORY https://github.com/assimp/assimp.git
#   GIT_TAG        v5.0.1
# )
# 
# set(ASSIMP_BUILD_TESTS OFF)
# 
# FetchContent_MakeAvailable(assimp)
