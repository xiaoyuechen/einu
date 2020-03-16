#include "ecs-engine/graphics/shader.h"

#include <stdexcept>

#include "ecs-engine/graphics/shader_util.h"
#include "ecs-engine/utility/file_reader.h"

namespace ecs {

namespace {

auto read_file(const char* filename) {
  auto file_reader = FileReader(filename);
  auto data = file_reader.GetContent();
  data.push_back(0);
  return data;
}
}  // namespace

Shader::Shader(Shader&& other) { swap(*this, other); }

Shader::~Shader() {
  if (shader_) {
    glDeleteShader(shader_);
  }
}

void Shader::LoadFromFile(const char* filename) {
  const auto data = read_file(filename);
  const auto source = data.data();
  LoadFromMemory(source);
}

void Shader::LoadFromMemory(const char* source) {
  glShaderSource(shader_, 1, &source, nullptr);
  glCompileShader(shader_);
  shader_util::CheckStatus(shader_util::Type::SHADER, shader_);
}

GLuint Shader::Get() const { return shader_; }

VertexShader::VertexShader() { shader_ = glCreateShader(GL_VERTEX_SHADER); }

VertexShader::VertexShader(VertexShader&& other)
    : Shader(std::move(other)) {}

FragmentShader::FragmentShader() {
  shader_ = glCreateShader(GL_FRAGMENT_SHADER);
}

FragmentShader::FragmentShader(FragmentShader&& other)
    : Shader(std::move(other)) {}

void swap(Shader& lhs, Shader& rhs) noexcept {
  std::swap(lhs.shader_, rhs.shader_);
}
}  // namespace ecs