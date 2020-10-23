#include "einu-graphics/sys_shader.h"

#include <glad/glad.h>

#include <fstream>
#include <sstream>

#include "einu-graphics/gl_error.h"

namespace einu {
namespace graphics {
namespace sys {

namespace {

enum class ShaderOrProgram { Shader, Program };

GLint GetStatus(ShaderOrProgram type, GLuint id) {
  GLint status = GL_TRUE;
  switch (type) {
    case ShaderOrProgram::Shader:
      glGetShaderiv(id, GL_COMPILE_STATUS, &status);
      break;
    case ShaderOrProgram::Program:
      glGetProgramiv(id, GL_LINK_STATUS, &status);
      break;
  }
  return status;
}

std::string GetInfoLog(ShaderOrProgram type, GLuint id) {
  std::string error_log(1024, '\0');
  switch (type) {
    case ShaderOrProgram::Shader:
      glGetShaderInfoLog(id, static_cast<GLsizei>(error_log.size()), nullptr,
                         error_log.data());
      break;
    case ShaderOrProgram::Program:
      glGetProgramInfoLog(id, static_cast<GLsizei>(error_log.size()), nullptr,
                          error_log.data());
      break;
  }
  return error_log;
}

void CheckStatus(ShaderOrProgram type, GLuint id) {
  GLint status = GetStatus(type, id);
  if (status == GL_FALSE) {
    auto error_log = GetInfoLog(type, id);
    throw GLError(error_log.c_str());
  }
}

}  // namespace

void CreateShader(ShaderType type, const char* name, const char* file_name,
                  sgln::ResourceTable& resource_table) {
  auto file = std::ifstream(file_name);
  if (!file.is_open()) {
    throw GLError{"Failed to open shader file"};
  }
  auto buffer = std::stringstream{};
  buffer << file.rdbuf();
  auto content = buffer.str();
  auto cstr = content.c_str();

  auto shader = std::uint32_t{};
  if (type == ShaderType::Vertex) {
    shader = glCreateShader(GL_VERTEX_SHADER);
  } else {
    shader = glCreateShader(GL_FRAGMENT_SHADER);
  }

  glShaderSource(shader, 1, &cstr, nullptr);
  glCompileShader(shader);

  CheckStatus(ShaderOrProgram::Shader, shader);

  auto key = sgln::ResourceTable::Key{};
  key.second = name;
  if (type == ShaderType::Vertex) {
    key.first = sgln::ResourceTable::Type::VertexShader;
  } else {
    key.first = sgln::ResourceTable::Type::FragmentShader;
  }

  resource_table.table.emplace(std::move(key), shader);
}

void DestroyShader(ShaderType type, const char* name,
                   sgln::ResourceTable& resource_table) {
  using Key = sgln::ResourceTable::Key;
  using Type = sgln::ResourceTable::Type;
  auto resource_type =
      type == ShaderType::Vertex ? Type::VertexShader : Type::FragmentShader;
  auto shader_it = resource_table.table.find(Key{resource_type, name});
  glDeleteShader(shader_it->second);
  resource_table.table.erase(shader_it);
}

void CreateProgram(const char* name, const char* vshader_name,
                   const char* fshader_name,
                   sgln::ResourceTable& resource_table) {
  using Key = sgln::ResourceTable::Key;
  using Type = sgln::ResourceTable::Type;
  auto vshader = resource_table.table.at(Key{Type::VertexShader, vshader_name});
  auto fshader =
      resource_table.table.at(Key{Type::FragmentShader, fshader_name});

  auto program = glCreateProgram();
  glAttachShader(program, vshader);
  glAttachShader(program, fshader);
  glLinkProgram(program);
  CheckStatus(ShaderOrProgram::Program, program);
  glDetachShader(program, vshader);
  glDetachShader(program, fshader);
}

void DeleteProgram(const char* name, sgln::ResourceTable& resource_table) {
  using Key = sgln::ResourceTable::Key;
  using Type = sgln::ResourceTable::Type;
  auto program_it = resource_table.table.find(Key{Type::ShaderProgram, name});
  glDeleteProgram(program_it->second);
  resource_table.table.erase(program_it);
}

}  // namespace sys
}  // namespace graphics
}  // namespace einu