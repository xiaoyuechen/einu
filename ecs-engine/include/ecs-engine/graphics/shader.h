#ifndef SHADER_H_
#define SHADER_H_

#include <glad/glad.h>

#include "ecs-engine/utility/noncopyable.h"

namespace ecs {

class Shader : Noncopyable {
 public:
  Shader() = default;
  virtual ~Shader();
  void LoadFromFile(const char* filename);
  GLuint Get() const;

 private:
  void Set(const GLchar* source);

 protected:
  GLuint shader_ = 0;

 public:
  friend void swap(Shader& lhs, Shader& rhs) noexcept;
};

class VertexShader : public Shader {
 public:
  VertexShader();
  explicit VertexShader(const char* filename);
};

class FragmentShader : public Shader {
 public:
  FragmentShader();
  explicit FragmentShader(const char* filename);
};

}  // namespace ecs

#endif  // SHADER_H_
