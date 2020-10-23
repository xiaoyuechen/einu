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