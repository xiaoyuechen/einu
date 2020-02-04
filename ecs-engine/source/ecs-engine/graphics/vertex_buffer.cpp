#include "ecs-engine/graphics/vertex_buffer.h"

namespace ecs {

VertexBuffer::VertexBuffer() { glGenBuffers(1, &vertex_buffer_); }

VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &vertex_buffer_); }

void VertexBuffer::Set(int size, const void* data) {
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
};

void VertexBuffer::Bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
}

void VertexBuffer::Render(GLenum primitive, int start, int count) {
  glDrawArrays(primitive, start, count);
}
}  // namespace ecs