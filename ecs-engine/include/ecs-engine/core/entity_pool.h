#pragma once

#include "ecs-engine/core/entity.h"
#include "ecs-engine/utility/fixed_size_pool.h"

namespace ecs {

using EntityPool = FixedSizePool<Entity>;

}