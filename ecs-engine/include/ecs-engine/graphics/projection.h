#ifndef PROJECTION_H_
#define PROJECTION_H_

#include "ecs-engine/math/glm.h"

namespace ecs {

struct Projection {
  enum class Type {
    ORTHOGRAPHIC,
    PERSPECTIVE,
  };

  struct OrthographicAttrib {
    float left = -1, right = 1, button = -1, top = 1;
    float near = 0.01f, far = 1000.f;
  };

  struct PerspectiveAttrib {
    float fov = 45.f;
    float aspect = 16.f / 9.f;
    float near = 0.01f, far = 1000.f;
  };

  union Attribute {
    OrthographicAttrib orthographic_attrib;
    PerspectiveAttrib perspective_attrib;
  };

  glm::mat4 GetProjectionMatrix() const;

  Type type = Type::ORTHOGRAPHIC;
  Attribute attrib{OrthographicAttrib{}};
};

Projection operator*(const Projection& projection, float ratio);
Projection operator*(float ratio, const Projection& projection);

}  // namespace ecs

#endif  // PROJECTION_H_
