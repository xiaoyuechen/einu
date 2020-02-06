#ifndef SINGLETON_CAMERA_COMPONENT_H_
#define SINGLETON_CAMERA_COMPONENT_H_

#include "ecs-engine/core/component_tag.h"
#include "ecs-engine/math/glm.h"

namespace ecs {

struct SingletonCameraComponent : public ComponentTag {
  glm::mat4 view =
      glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
  glm::mat4 projection = glm::ortho(-1, 1, -1, 1);

  glm::mat4 GetCameraMatrix() const;
};

//////////////////////////////////////////////////////////////////////////

inline glm::mat4 SingletonCameraComponent::GetCameraMatrix() const {
  return projection * view;
}
}  // namespace ecs

#endif  // SINGLETON_CAMERA_COMPONENT_H_
