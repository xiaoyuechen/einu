#include "einu-core/internal/world_pool.h"

namespace einu {
namespace internal {

void WorldPool::SetPolicyImpl(const Policy& policy) {
  pool_.SetGrowth(policy.growth_func);
  pool_.GrowExtra(policy.init_size);
}

IWorld& WorldPool::AcquireImpl() { return pool_.Acquire(); }

void WorldPool::ReleaseImpl(const IWorld& world) {
  pool_.Release(reinterpret_cast<const World&>(world));
}

WorldPool::size_type WorldPool::SizeImpl() const noexcept {
  return pool_.Size();
}

}  // namespace internal
}  // namespace einu