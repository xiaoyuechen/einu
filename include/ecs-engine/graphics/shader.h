#pragma once

#include <glad/glad.h>

#include "ecs-engine/utility/noncopyable.h"

namespace ecs {

class Shader : Noncopyable {
 public:
  Shader() = default;
  Shader(Shader&& other);

  virtual ~Shader();
  void LoadFromFile(const char* filename);
  void LoadFromMemory(const char* source);
  GLuint Get() const;

 protected:
  GLuint shader_ = 0;

 public:
  friend void swap(Shader& lhs, Shader& rhs) noexcept;
};

void swap(Shader& lhs, Shader& rhs) noexcept;

class VertexShader : public Shader {
 public:
  VertexShader();
  VertexShader(VertexShader&& other);
};

class FragmentShader : public Shader {
 public:
  FragmentShader();
  FragmentShader(FragmentShader&& other);
};

}  // namespace ecs