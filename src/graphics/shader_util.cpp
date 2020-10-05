#include "einu-engine/graphics/shader_util.h"

#include <string>

#include "einu-engine/graphics/gl_error.h"

namespace einu {

namespace shader_util {

namespace {
GLint get_status(Type type, GLuint id) {
  GLint status = GL_TRUE;
  switch (type) {
    case Type::SHADER:
      glGetShaderiv(id, GL_COMPILE_STATUS, &status);
      break;
    case Type::PROGRAM:
      glGetProgramiv(id, GL_LINK_STATUS, &status);
      break;
  }
  return status;
}

std::string get_info_log(Type type, GLuint id) {
  std::string error_log(1024, '\0');
  switch (type) {
    case Type::SHADER:
      glGetShaderInfoLog(id,
                         static_cast<GLsizei>(error_log.size()),
                         nullptr,
                         &error_log.front());
      break;
    case Type::PROGRAM:
      glGetProgramInfoLog(id,
                          static_cast<GLsizei>(error_log.size()),
                          nullptr,
                          &error_log.front());
      break;
  }
  return error_log;
}
}  // namespace

void CheckStatus(Type type, GLuint id) {
  GLint status = get_status(type, id);
  if (status == GL_FALSE) {
    auto error_log = get_info_log(type, id);
    throw GLError(error_log.c_str());
  }
}
}  // namespace shader_util
}  // namespace einu