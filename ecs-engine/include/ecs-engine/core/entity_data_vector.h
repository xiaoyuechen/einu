#pragma once

#include <functional>
#include <vector>

#include "ecs-engine/core/entity_data.h"

namespace ecs {

using EntityDataVector = std::vector<std::reference_wrapper<EntityData>>;

}