#include "einu-engine/graphics/vertex_buffer.h"

namespace einu {

VertexBuffer::VertexBuffer() { glGenBuffers(1, &vertex_buffer_); }

VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &vertex_buffer_); }

void VertexBuffer::Set(std::size_t size, const void* data) {
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
};

void VertexBuffer::Bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
}

void VertexBuffer::Render(GLenum primitive, int start, uint32_t count) {
  glDrawArrays(primitive, start, count);
}

void VertexBuffer::RenderInstance(GLenum primitive,
                                  int start,
                                  uint32_t count,
                                  uint32_t instance_count) {
  glDrawArraysInstanced(primitive, start, count, instance_count);
}

}  // namespace einu