#pragma once

#include <glad/glad.h>
#include <cstddef>
#include <cstdint>

#include "ecs-engine/utility/noncopyable.h"

namespace ecs {

class VertexBuffer : Noncopyable {
 public:
  VertexBuffer();
  ~VertexBuffer();
  void Set(std::size_t size, const void* data);
  void Bind() const;
  void Render(GLenum primitive, int start, uint32_t count);
  void RenderInstance(GLenum primitive,
                      int start,
                      uint32_t count,
                      uint32_t instance_count);

 private:
  GLuint vertex_buffer_ = 0;
};
}  // namespace ecs

