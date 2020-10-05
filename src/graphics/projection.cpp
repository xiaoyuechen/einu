#include "einu-engine/graphics/projection.h"

namespace einu {

glm::mat4 einu::Projection::GetProjectionMatrix() const {
  if (type == Projection::Type::ORTHOGRAPHIC) {
    const auto& ortho_attrib = attrib.orthographic_attrib;
    return glm::ortho(ortho_attrib.left, ortho_attrib.right,  //
                      ortho_attrib.button, ortho_attrib.top,  //
                      ortho_attrib.near, ortho_attrib.far);
  } else {
    const auto& pers_attrib = attrib.perspective_attrib;
    return glm::perspective(pers_attrib.fov, pers_attrib.aspect,
                            pers_attrib.near, pers_attrib.far);
  }
}

Projection::OrthographicAttrib operator*(
    const Projection::OrthographicAttrib& attrib, float ratio) {
  auto copy = attrib;
  copy.left *= ratio;
  copy.right *= ratio;
  copy.top *= ratio;
  copy.button *= ratio;
  return copy;
}

Projection operator*(const Projection& projection, float ratio) {
  if (projection.type == Projection::Type::ORTHOGRAPHIC) {
    auto copy = projection;
    auto& attrib = copy.attrib.orthographic_attrib;
    attrib.left *= ratio;
    attrib.right *= ratio;
    attrib.top *= ratio;
    attrib.button *= ratio;
    return copy;
  }
  return projection;
}

Projection operator*(float ratio, const Projection& projection) {
  return projection * ratio;
}

}  // namespace einu
