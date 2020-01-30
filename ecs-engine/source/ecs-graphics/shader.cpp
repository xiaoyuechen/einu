#include "ecs-engine/graphics/shader.h"

#include <stdexcept>

#include "ecs-engine/graphics/shader_util.h"
#include "ecs-engine/file-system/file_system.h"

namespace ecs {

namespace {

auto read_file(const char* filename) {
  auto data = file_system::ReadFileContent(filename);
  data.push_back(0);
  return data;
}
}  // namespace

Shader::~Shader() { glDeleteShader(shader_); }

void Shader::LoadFromFile(const char* filename) {
  const auto data = read_file(filename);
  const auto source = data.data();
  Set(source);
}

GLuint Shader::Get() const { return shader_; }

void Shader::Set(const GLchar* source) {
  glShaderSource(shader_, 1, &source, nullptr);
  glCompileShader(shader_);
  shader_util::CheckStatus(shader_util::Type::SHADER, shader_);
}

VertexShader::VertexShader() { shader_ = glCreateShader(GL_VERTEX_SHADER); }

VertexShader::VertexShader(const char* filename)
    : VertexShader() {
  LoadFromFile(filename);
}

FragmentShader::FragmentShader() {
  shader_ = glCreateShader(GL_FRAGMENT_SHADER);
}

FragmentShader::FragmentShader(const char* filename)
    : FragmentShader() {
  LoadFromFile(filename);
}

void swap(Shader& lhs, Shader& rhs) noexcept {
  std::swap(lhs.shader_, rhs.shader_);
}
}  // namespace ecs