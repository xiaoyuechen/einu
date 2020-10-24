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

#include "einu-engine/graphics/resource_type.h"
#include "einu-engine/graphics/singlenents.h"

namespace einu {
namespace graphics {
namespace sys {

template <ResourceType t, typename... Args>
void Create(sgln::ResourceTable& resource_table, const char* name,
            Args... args);

template <ResourceType t, typename... Args>
void Destroy(sgln::ResourceTable& resource_table, const char* name,
             Args... args);

template <>
void Create<ResourceType::VertexArray>(sgln::ResourceTable& resource_table,
                                       const char* name);

template <>
void Destroy<ResourceType::VertexArray>(sgln::ResourceTable& resource_table,
                                        const char* name);

template <>
void Create<ResourceType::VertexBuffer>(sgln::ResourceTable& resource_table,
                                        const char* name);

template <>
void Destroy<ResourceType::VertexBuffer>(sgln::ResourceTable& resource_table,
                                         const char* name);

template <>
void Create<ResourceType::VertexShader, const char*>(
    sgln::ResourceTable& resource_table, const char* name,
    const char* file_name);

template <>
void Destroy<ResourceType::VertexShader>(sgln::ResourceTable& resource_table,
                                         const char* name);

template <>
void Create<ResourceType::FragmentShader, const char*>(
    sgln::ResourceTable& resource_table, const char* name,
    const char* file_name);

template <>
void Destroy<ResourceType::FragmentShader>(sgln::ResourceTable& resource_table,
                                           const char* name);

template <>
void Create<ResourceType::ShaderProgram, const char*, const char*>(
    sgln::ResourceTable& resource_table, const char* name,
    const char* vshader_name, const char* fshader_name);

template <>
void Destroy<ResourceType::ShaderProgram>(sgln::ResourceTable& resource_table,
                                          const char* name);

}  // namespace sys
}  // namespace graphics
}  // namespace einu
