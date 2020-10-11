#include "einu-core/internal/world_pool.h"

namespace einu {
namespace internal {

void WorldPool::SetPolicyImpl(const Policy& policy) {
  pool_.SetGrowth(policy.growth_func);
  pool_.GrowExtra(policy.init_size);
}

IWorld& WorldPool::AcquireImpl() {
  auto& world = pool_.Acquire();
  return world;
}

void WorldPool::ReleaseImpl(const IEntity& ett) noexcept {
}

WorldPool::size_type WorldPool::SizeImpl() const noexcept {
  return 0;
}

}  // namespace internal
}  // namespace einu