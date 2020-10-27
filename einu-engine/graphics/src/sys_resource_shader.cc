// Copyright (C) 2020  Xiaoyue Chen
//
// This file is part of EINU Engine.
// See <https://github.com/xiaoyuechen/einu.git>.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <glad/glad.h>

#include <cassert>
#include <fstream>
#include <sstream>

#include "einu-engine/graphics/graphics_error.h"
#include "einu-engine/graphics/sys_resource.h"
#include "src/sys_resource_helper.h"

namespace einu {
namespace graphics {
namespace sys {

namespace {

enum class ShaderType { Vertex, Fragment };

ResourceType ToResourceType(ShaderType shader_type) noexcept {
  auto resource_type = shader_type == ShaderType::Vertex
                           ? ResourceType::VertexShader
                           : ResourceType::FragmentShader;
  return resource_type;
}

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
    throw GraphicsError(error_log.c_str());
  }
}

ResourceID CreateShader(ShaderType type, sgl::GLResourceTable& resource_table,
                        const char* name, const char* file_name) {
  return CreateHelper(resource_table, ToResourceType(type), name, [=]() {
    auto file = std::ifstream(file_name);
    if (!file.is_open()) {
      throw GraphicsError{"Failed to open shader file"};
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
    return shader;
  });
}

void DestroyShader(ShaderType type, sgl::GLResourceTable& resource_table,
                   const char* name) {
  DestroyHelper(resource_table, ToResourceType(type), name, glDeleteShader);
}

}  // namespace

template <>
ResourceID Create<ResourceType::VertexShader, const char*>(
    sgl::GLResourceTable& resource_table, const char* name,
    const char* file_name) {
  return CreateShader(ShaderType::Vertex, resource_table, name, file_name);
}

template <>
void Destroy<ResourceType::VertexShader>(sgl::GLResourceTable& resource_table,
                                         const char* name) {
  DestroyShader(ShaderType::Vertex, resource_table, name);
}

template <>
ResourceID Create<ResourceType::FragmentShader, const char*>(
    sgl::GLResourceTable& resource_table, const char* name,
    const char* file_name) {
  return CreateShader(ShaderType::Fragment, resource_table, name, file_name);
}

template <>
void Destroy<ResourceType::FragmentShader>(sgl::GLResourceTable& resource_table,
                                           const char* name) {
  DestroyShader(ShaderType::Fragment, resource_table, name);
}

template <>
ResourceID Create<ResourceType::ShaderProgram, const char*, const char*>(
    sgl::GLResourceTable& resource_table, const char* name,
    const char* vshader_name, const char* fshader_name) {
  return CreateHelper(resource_table, ResourceType::ShaderProgram, name,
                      [=, &resource_table] {
                        using Key = sgl::GLResourceTable::Key;
                        auto vshader = resource_table.table.at(
                            Key{ResourceType::VertexShader, vshader_name});
                        auto fshader = resource_table.table.at(
                            Key{ResourceType::FragmentShader, fshader_name});

                        auto program = glCreateProgram();
                        glAttachShader(program, vshader);
                        glAttachShader(program, fshader);
                        glLinkProgram(program);
                        CheckStatus(ShaderOrProgram::Program, program);
                        glDetachShader(program, vshader);
                        glDetachShader(program, fshader);
                        return program;
                      });
}

template <>
void Destroy<ResourceType::ShaderProgram>(sgl::GLResourceTable& resource_table,
                                          const char* name) {
  DestroyHelper(resource_table, ResourceType::ShaderProgram, name,
                glDeleteProgram);
}

}  // namespace sys
}  // namespace graphics
}  // namespace einu
