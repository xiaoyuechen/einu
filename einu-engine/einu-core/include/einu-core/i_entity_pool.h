#pragma once

#include <cstdint>

#include "einu-core/i_entity.h"
#include "einu-core/internal/i_pool.h"
#include "einu-core/pool_policy.h"

namespace einu {

using IEntityPool = internal::IPool<IEntity, PoolPolicy<>>;

}  // namespace einu