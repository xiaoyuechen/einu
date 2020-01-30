#ifndef TEXTURE_H_
#define TEXTURE_H_

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

 private:
  GLuint texture_;
};
}  // namespace ecs

#endif  // TEXTURE_H_
