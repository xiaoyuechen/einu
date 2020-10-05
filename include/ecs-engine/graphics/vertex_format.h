#pragma once

#include <glad/glad.h>

#include <cstdint>
#include <vector>

namespace einu {

class VertexFormat {
 public:
  struct Attribute {
    GLuint index = 0;
    GLuint size = 0;
    GLenum type = 0;
    GLboolean normalized = false;
    std::size_t offset = 0;
    uint32_t divisor = 0;
  };

  void AddAttribute(uint32_t index,
                    uint32_t size,
                    GLenum type,
                    bool normalized,
                    uint32_t divisor = 0);
  bool IsValid() const;
  void Enable();
  void Disable();

  GLsizei stride_ = 0;
  std::vector<Attribute> attributes_{};
};

}  // namespace einu

