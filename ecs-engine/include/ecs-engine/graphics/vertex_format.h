#ifndef VERTEX_FORMAT_H_
#define VERTEX_FORMAT_H_

#include <glad/glad.h>

#include <array>
#include <cstdint>

namespace ecs {

constexpr uint32_t kAttributeCount = 4;

class VertexFormat {
 public:
  struct Attribute {
    GLuint index = 0;
    GLuint size = 0;
    GLenum type = 0;
    GLboolean normalized = false;
    uint64_t offset = 0;
  };

  void AddAttribute(uint32_t index,
                     uint32_t size,
                     GLenum type,
                     bool normalized);
  void AddAttribute(const Attribute& attribute);
  bool IsValid() const;
  void Bind() const;

 private:
  GLsizei stride_ = 0;
  uint32_t attribute_count_ = 0;
  std::array<Attribute, kAttributeCount> attributes_{};
};

}  // namespace ecs

#endif  // VERTEX_FORMAT_H_
