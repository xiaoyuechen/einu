#include "einu-core/i_world.h"
#include "einu-core/internal/i_pool.h"
#include "einu-core/pool_policy.h"

namespace einu {

using IWorldPool = internal::IPool<IWorld, PoolPolicy<>>;

}  // namespace einu