#pragma once

#include <glad/glad.h>

#include "ecs-engine/utility/Noncopyable.h"

namespace ecs {

class Texture : Noncopyable {
 public:
  Texture();
  ~Texture();

  void LoadFromFile(const char* filename);
  void Bind() const;
  GLuint Get() const;

  const int Width() const;
  const int Height() const;

 private:
  GLuint texture_ = 0;
  int width_ = 0;
  int height_ = 0;
};
}  // namespace ecs

