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
void Create(sgl::ResourceTable& resource_table, const char* name, Args... args);

template <ResourceType t, typename... Args>
void Destroy(sgl::ResourceTable& resource_table, const char* name,
             Args... args);

template <>
void Create<ResourceType::VertexArray>(sgl::ResourceTable& resource_table,
                                       const char* name);

template <>
void Destroy<ResourceType::VertexArray>(sgl::ResourceTable& resource_table,
                                        const char* name);

template <>
void Create<ResourceType::VertexBuffer>(sgl::ResourceTable& resource_table,
                                        const char* name);

template <>
void Destroy<ResourceType::VertexBuffer>(sgl::ResourceTable& resource_table,
                                         const char* name);

template <>
void Create<ResourceType::VertexShader, const char*>(
    sgl::ResourceTable& resource_table, const char* name,
    const char* file_name);

template <>
void Destroy<ResourceType::VertexShader>(sgl::ResourceTable& resource_table,
                                         const char* name);

template <>
void Create<ResourceType::FragmentShader, const char*>(
    sgl::ResourceTable& resource_table, const char* name,
    const char* file_name);

template <>
void Destroy<ResourceType::FragmentShader>(sgl::ResourceTable& resource_table,
                                           const char* name);

template <>
void Create<ResourceType::ShaderProgram, const char*, const char*>(
    sgl::ResourceTable& resource_table, const char* name,
    const char* vshader_name, const char* fshader_name);

template <>
void Destroy<ResourceType::ShaderProgram>(sgl::ResourceTable& resource_table,
                                          const char* name);

template <>
void Create<ResourceType::Texture, const char*>(
    sgl::ResourceTable& resource_table, const char* name,
    const char* file_name);

template <>
void Destroy<ResourceType::Texture>(sgl::ResourceTable& resource_table,
                                    const char* name);

template <>
void Create<ResourceType::Sampler>(sgl::ResourceTable& resource_table,
                                   const char* name);

template <>
void Destroy<ResourceType::Sampler>(sgl::ResourceTable& resource_table,
                                    const char* name);

}  // namespace sys
}  // namespace graphics
}  // namespace einu
