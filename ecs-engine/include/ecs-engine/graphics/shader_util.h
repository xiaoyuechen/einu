#ifndef SHADER_UTIL_H_
#define SHADER_UTIL_H_

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

#endif  // SHADER_UTIL_H_
