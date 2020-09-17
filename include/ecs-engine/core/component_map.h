#pragma once

#include "ecs-engine/core/i_component.h"
#include "ecs-engine/utility/container/linear_search_map.h"
#include "ecs-engine/utility/rtti/class_index.h"

namespace ecs {
using ComponentMap = LinearSearchMap<rtti::ClassIndex, IComponent*>;
}  // namespace ecs
