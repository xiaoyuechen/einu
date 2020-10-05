#pragma once

#include <glad/glad.h>

#include "einu-engine/utility/noncopyable.h"

namespace einu {

class VertexArray : Noncopyable {
 public:
  VertexArray();
  ~VertexArray();
  void Bind() const;

 private:
  GLuint vertex_array_ = 0;
};

}  // namespace einu

