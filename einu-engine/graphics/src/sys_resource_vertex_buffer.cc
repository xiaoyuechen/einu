#include <glad/glad.h>

#include "einu-engine/graphics/sys_resource.h"

namespace einu {
namespace graphics {
namespace sys {

template <>
void Create<ResourceType::VertexBuffer>(sgln::ResourceTable& resource_table,
                                        const char* name) {
  GLuint vertex_buffer;
  glGenBuffers(1, &vertex_buffer);

  using Key = sgln::ResourceTable::Key;
  resource_table.table.emplace(Key{ResourceType::VertexBuffer, name},
                               vertex_buffer);
}

template <>
void Destroy<ResourceType::VertexBuffer>(sgln::ResourceTable& resource_table,
                                         const char* name) {
  using Key = sgln::ResourceTable::Key;
  auto it = resource_table.table.find(Key{ResourceType::VertexBuffer, name});
  glDeleteBuffers(1, &it->second);
  resource_table.table.erase(it);
}

}  // namespace sys
}  // namespace graphics
}  // namespace einu