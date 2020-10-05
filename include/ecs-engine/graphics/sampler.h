#pragma once

#include <glad/glad.h>

#include "einu-engine/utility/Noncopyable.h"

namespace einu {

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
}  // namespace einu