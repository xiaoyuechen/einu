#pragma once

#include <glad/glad.h>

#include "ecs-engine/utility/Noncopyable.h"

namespace ecs {

class Sampler : Noncopyable {
 public:
  Sampler();
  ~Sampler();
  void Set(const GLenum filter,
           const GLenum address_mode_u,
           const GLenum address_mode_v);
  void Bind() const;

 private:
  GLuint sampler_ = 0;
};
}  // namespace ecs