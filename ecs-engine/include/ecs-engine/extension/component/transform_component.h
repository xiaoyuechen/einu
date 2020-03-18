#pragma once

#include "ecs-engine/core/component_tag.h"
#include "ecs-engine/math/transform.h"

namespace ecs {
struct TransformComponent : public ComponentTag,
                            public Transform<transform_policy::NoCache> {};
}