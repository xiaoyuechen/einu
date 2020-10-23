#pragma once

#include "einu-graphics/singlenents.h"

namespace einu {
namespace graphics {
namespace sys {

enum class ShaderType { Vertex, Fragment };

void CreateShader(ShaderType type, const char* name, const char* file_name,
                  sgln::ResourceTable& resource_table);

void DestroyShader(ShaderType type, const char* name,
                   sgln::ResourceTable& resource_table);

void CreateProgram(const char* name, const char* vshader_name,
                   const char* fshader_name,
                   sgln::ResourceTable& resource_table);

void DeleteProgram(const char* name, sgln::ResourceTable& resource_table);

}  // namespace sys
}  // namespace graphics
}  // namespace einu