#pragma once

#include <vector>
#include <string>

#include "einu-engine/graphics/camera.h"
#include "einu-engine/graphics/sampler.h"
#include "einu-engine/graphics/shader_program.h"
#include "einu-engine/graphics/texture.h"
#include "einu-engine/graphics/vertex_buffer.h"
#include "einu-engine/graphics/vertex_format.h"

namespace einu {

class BitmapFont {
 public:
  BitmapFont(const ShaderProgram& shader_program, const Texture& texture);

  void Render(
      float x, float y, float size, bool is_active, const std::string& text);
  void Flush(const Camera& camera);

 private:
  struct Vertex {
    float x, y;
    float u, v;
    float is_active;
  };

 private:
  const ShaderProgram& program_;
  const Texture& texture_;
  VertexFormat format_;
  VertexBuffer buffer_;
  std::vector<Vertex> vertices_;
};

}  // namespace einu