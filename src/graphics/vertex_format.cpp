#include "einu-engine/graphics/vertex_format.h"

#include <cassert>

namespace einu {

namespace {

constexpr uint32_t SizeOfGLType(GLenum type) {
  switch (type) {
    case GL_FLOAT:
      return sizeof(GLfloat);
    case GL_UNSIGNED_BYTE:
      return sizeof(uint8_t);
  }
  assert(false && "incorrect type");
  return 0;
}
}  // namespace

void VertexFormat::AddAttribute(uint32_t index,
                                uint32_t size,
                                GLenum type,
                                bool normalized,
                                uint32_t divisor) {
  const Attribute attrib{index,
                         size,
                         type,
                         normalized,
                         static_cast<std::size_t>(stride_),
                         divisor};
  attributes_.push_back(attrib);
  stride_ += size * SizeOfGLType(type);
}

bool VertexFormat::IsValid() const { return attributes_.size() > 0; }

void VertexFormat::Enable() {
  for (const auto& attrib : attributes_) {
    glEnableVertexAttribArray(attrib.index);
    glVertexAttribPointer(attrib.index,
                          attrib.size,
                          attrib.type,
                          attrib.normalized,
                          stride_,
                          (const void*)attrib.offset);
    glVertexAttribDivisor(attrib.index, attrib.divisor);
  }
}

void VertexFormat::Disable() {
  for (const auto& attrib : attributes_) {
    glDisableVertexAttribArray(attrib.index);
  }
}

}  // namespace einu