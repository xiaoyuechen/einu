#include <glad/glad.h>

#include <cassert>

#include "einu-engine/graphics/sys_resource.h"

namespace einu {
namespace graphics {
namespace sys {

template <>
void Create<ResourceType::VertexArray>(sgln::ResourceTable& resource_table,
                                       const char* name) {
  GLuint vertex_array;
  glGenVertexArrays(1, &vertex_array);
  using Key = sgln::ResourceTable::Key;
  resource_table.table.emplace(Key{ResourceType::VertexArray, name},
                               vertex_array);
}

template <>
void Destroy<ResourceType::VertexArray>(sgln::ResourceTable& resource_table,
                                        const char* name) {
  using Key = sgln::ResourceTable::Key;
  auto it = resource_table.table.find(Key{ResourceType::VertexArray, name});
  assert(it != resource_table.table.end() && "Vertex array does not exist");
  glDeleteVertexArrays(1, &it->second);
  resource_table.table.erase(it);
}

}  // namespace sys
}  // namespace graphics
}  // namespace einu