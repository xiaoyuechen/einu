#pragma once

#include <glad/glad.h>

#include "ecs-engine/utility/noncopyable.h"

namespace ecs {

class VertexArray : Noncopyable {
 public:
  VertexArray();
  ~VertexArray();
  void Bind() const;

 private:
  GLuint vertex_array_ = 0;
};

}  // namespace ecs

