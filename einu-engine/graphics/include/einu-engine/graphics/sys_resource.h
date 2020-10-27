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

#pragma once

#include "einu-engine/graphics/resource.h"
#include "einu-engine/graphics/sgl_resource_table.h"

namespace einu {
namespace graphics {
namespace sys {

template <ResourceType t, typename... Args>
ResourceID Create(sgl::GLResourceTable& resource_table, const char* name,
                  Args... args);

template <ResourceType t, typename... Args>
void Destroy(sgl::GLResourceTable& resource_table, const char* name,
             Args... args);

template <>
ResourceID Create<ResourceType::VertexArray>(
    sgl::GLResourceTable& resource_table, const char* name);

template <>
void Destroy<ResourceType::VertexArray>(sgl::GLResourceTable& resource_table,
                                        const char* name);

template <>
ResourceID Create<ResourceType::VertexBuffer>(
    sgl::GLResourceTable& resource_table, const char* name);

template <>
void Destroy<ResourceType::VertexBuffer>(sgl::GLResourceTable& resource_table,
                                         const char* name);

template <>
ResourceID Create<ResourceType::VertexShader, const char*>(
    sgl::GLResourceTable& resource_table, const char* name,
    const char* file_name);

template <>
void Destroy<ResourceType::VertexShader>(sgl::GLResourceTable& resource_table,
                                         const char* name);

template <>
ResourceID Create<ResourceType::FragmentShader, const char*>(
    sgl::GLResourceTable& resource_table, const char* name,
    const char* file_name);

template <>
void Destroy<ResourceType::FragmentShader>(sgl::GLResourceTable& resource_table,
                                           const char* name);

template <>
ResourceID Create<ResourceType::ShaderProgram, const char*, const char*>(
    sgl::GLResourceTable& resource_table, const char* name,
    const char* vshader_name, const char* fshader_name);

template <>
void Destroy<ResourceType::ShaderProgram>(sgl::GLResourceTable& resource_table,
                                          const char* name);

template <>
ResourceID Create<ResourceType::Texture, const char*>(
    sgl::GLResourceTable& resource_table, const char* name,
    const char* file_name);

template <>
void Destroy<ResourceType::Texture>(sgl::GLResourceTable& resource_table,
                                    const char* name);

template <>
ResourceID Create<ResourceType::Sampler>(sgl::GLResourceTable& resource_table,
                                         const char* name);

template <>
void Destroy<ResourceType::Sampler>(sgl::GLResourceTable& resource_table,
                                    const char* name);

}  // namespace sys
}  // namespace graphics
}  // namespace einu
