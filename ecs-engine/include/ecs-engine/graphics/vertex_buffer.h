#ifndef VERTEX_BUFFER_H_
#define VERTEX_BUFFER_H_

#include <glad/glad.h>

#include "ecs-engine/utility/noncopyable.h"

namespace ecs {

class VertexBuffer : Noncopyable {
 public:
  VertexBuffer();
  ~VertexBuffer();
  void Set(int size, const void* data);
  void Bind() const;
  void Render(GLenum primitive, int start, int count);

 private:
  GLuint vertex_buffer_ = 0;
};
}  // namespace ecs

#endif  // VERTEX_BUFFER_H_
