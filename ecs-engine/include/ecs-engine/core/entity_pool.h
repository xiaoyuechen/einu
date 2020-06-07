#pragma once

#include "ecs-engine/core/entity_data.h"
#include "ecs-engine/utility/fixed_size_pool.h"

namespace ecs {

using EntityPool = FixedSizePool<EntityData>;

}