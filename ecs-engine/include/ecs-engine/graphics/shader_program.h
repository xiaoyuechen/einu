#pragma once

#include "ecs-engine/math/glm.h"
#include "ecs-engine/utility/Noncopyable.h"
#include "shader.h"

namespace ecs {

class ShaderProgram : Noncopyable {
 public:
  ShaderProgram();
  ShaderProgram(const VertexShader& vertex_shader,
          const FragmentShader& fragment_shader);
  ~ShaderProgram();

  void Set(const VertexShader& vertex_shader,
           const FragmentShader& fragment_shader);
  GLuint Get() const;
  void Bind() const;

  GLuint GetAttributeLocation(const char* name) const;
  GLuint GetUniformLocation(const char* name) const;
  void SetUniform(const char* name, const glm::mat4& mat) const;
  void SetUniform(const char* name, const glm::vec4& mat) const;

 private:
  GLuint program_ = 0;
};

}  // namespace ecs