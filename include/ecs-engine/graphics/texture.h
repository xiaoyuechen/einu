#pragma once

#include <glad/glad.h>

#include "einu-engine/utility/Noncopyable.h"

namespace einu {

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
}  // namespace einu

