#include "ecs-engine/graphics/bitmap_font.h"

#include "ecs-engine/math/glm.h"

namespace ecs {

BitmapFont::BitmapFont(const ShaderProgram& shader_program,
                       const Texture& texture)
    : program_(shader_program)
    , texture_(texture) {
  format_.AddAttribute(0, 2, GL_FLOAT, false);
  format_.AddAttribute(1, 2, GL_FLOAT, false);
  format_.AddAttribute(2, 1, GL_FLOAT, false);
}

constexpr int CHARACTERS_PER_ROW = 16;
void BitmapFont::Render(float pos_x,
                        float pos_y,
                        float size,
                        bool is_active,
                        const std::string& text) {
  const float duv = 1.f / 16.f;

  for (const auto& character : text) {
    float is_active_f = static_cast<float>(is_active);
    int index = character - ' ';

    int col = index % CHARACTERS_PER_ROW;
    int row = index / CHARACTERS_PER_ROW + 2;

    float u = (float)col / 16.f;
    float v = (float)row / 16.f;

    Vertex verts[] = {
        {pos_x, pos_y, u, v, is_active_f},
        {pos_x, pos_y + size, u, v + duv, is_active_f},
        {pos_x + size, pos_y + size, u + duv, v + duv, is_active_f},

        {pos_x, pos_y, u, v, is_active_f},
        {pos_x + size, pos_y + size, u + duv, v + duv, is_active_f},
        {pos_x + size, pos_y, u + duv, v, is_active_f},
    };

    for (const auto& vert : verts) {
      vertices_.push_back(vert);
    }

    pos_x += size;
  }
}

void BitmapFont::Flush(const Camera& camera) {
  GLsizei size = (GLsizei)(sizeof(Vertex) * vertices_.size());
  buffer_.Set(size, vertices_.data());
  glDisable(GL_DEPTH_TEST);
  program_.Bind();
  program_.SetUniform("camera", camera.get_camera_matrix());
  buffer_.Bind();
  format_.Enable();
  texture_.Bind();
  glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices_.size());
  vertices_.clear();
}

}  // namespace ecs