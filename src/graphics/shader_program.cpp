#include "einu-engine/graphics/shader_program.h"

#include <cassert>

#include "einu-engine/graphics/gl_error.h"
#include "einu-engine/graphics/shader_util.h"

namespace einu {
ShaderProgram::ShaderProgram() { program_ = glCreateProgram(); }

ShaderProgram::ShaderProgram(const VertexShader& vertex_shader,
                             const FragmentShader& fragment_shader)
    : ShaderProgram() {
  Set(vertex_shader, fragment_shader);
}

ShaderProgram::~ShaderProgram() { glDeleteProgram(program_); }

void ShaderProgram::Set(const VertexShader& vertex_shader,
                        const FragmentShader& fragment_shader) {
  glAttachShader(program_, vertex_shader.Get());
  glAttachShader(program_, fragment_shader.Get());
  glLinkProgram(program_);
  shader_util::CheckStatus(shader_util::Type::PROGRAM, program_);
  glDetachShader(program_, vertex_shader.Get());
  glDetachShader(program_, fragment_shader.Get());
}

GLuint ShaderProgram::Get() const { return program_; }

void ShaderProgram::Bind() const { glUseProgram(program_); }

GLuint ShaderProgram::GetAttributeLocation(const char* name) const {
  Bind();
  auto location = glGetAttribLocation(program_, name);
  if (location < 0) {
    throw GLError("failed to get shader attribute");
  }
  return location;
}

GLuint ShaderProgram::GetUniformLocation(const char* name) const {
  Bind();
  auto location = glGetUniformLocation(program_, name);
  if (location < 0) {
    throw GLError("failed to get shader uniform location");
  }
  return location;
}

void ShaderProgram::SetUniform(const char* name, const glm::mat4& mat) const {
  auto location = GetUniformLocation(name);
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void ShaderProgram::SetUniform(const char* name, const glm::vec4& vec) const {
  auto location = GetUniformLocation(name);
  glUniform4fv(location, 1, glm::value_ptr(vec));
}

}  // namespace einu