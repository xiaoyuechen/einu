#pragma once

#include <glad/glad.h>

namespace ecs {
namespace shader_util {
enum class Type {
  SHADER,
  PROGRAM,
};

void CheckStatus(Type type, GLuint id);
}  // namespace shader_util
}  // namespace ecs

