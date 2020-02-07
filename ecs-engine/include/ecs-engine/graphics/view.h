#ifndef VIEW_H_
#define VIEW_H_

#include "ecs-engine/math/glm.h"

namespace ecs {

struct View {
  glm::mat4 GetViewMatrix() const;

  glm::vec3 position{0, 0, 3}, target{0, 0, 0};
  glm::vec3 up{0, 1, 0};
};

}  // namespace ecs

#endif  // VIEW_H_
