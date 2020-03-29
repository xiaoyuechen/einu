#pragma once

#include "ecs-engine/ai/behavior_tree/root.h"
#include "ecs-engine/core/component_tag.h"

namespace ecs {

struct BehaviorTreeComponent : public ComponentTag {
  ai::bt::Root root{};
};

}  // namespace ecs