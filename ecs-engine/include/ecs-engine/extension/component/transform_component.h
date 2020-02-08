#ifndef TRANSFORM_COMPONENT_H_
#define TRANSFORM_COMPONENT_H_

#include "ecs-engine/core/component_tag.h"
#include "ecs-engine/math/transform.h"

namespace ecs {
struct TransformComponent : public ComponentTag,
                            public Transform<transform_policy::NoCache> {};
}


#endif  // TRANSFORM_COMPONENT_H_