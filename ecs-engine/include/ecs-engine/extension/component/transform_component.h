#ifndef TRANSFORM_COMPONENT_H_
#define TRANSFORM_COMPONENT_H_

#include "ecs-engine/core/component_tag.h"
#include "ecs-engine/math/glm.h"

namespace ecs {

struct TransformComponent : public ComponentTag, public glm::mat4 {
  using glm::mat4::mat4;
  TransformComponent();
};

//////////////////////////////////////////////////////////////////////////

inline TransformComponent::TransformComponent()
    : glm::mat4(glm::mat4(1.f)) {}

}  // namespace ecs

#endif  // TRANSFORM_COMPONENT_H_
