#include "einu-core/internal/world_pool.h"

namespace einu {
namespace internal {

void WorldPool::SetPolicyImpl(const Policy& policy) {
  pool_.SetGrowth(policy.growth_func);
  pool_.GrowExtra(policy.init_size);
}

IWorld& WorldPool::AcquireImpl() {
  auto& world = pool_.Acquire();
  world.singlentity = &ett_pool_.Acquire();
  world.entity_table.clear();
  return world;
}

void WorldPool::ReleaseImpl(const IWorld& world) {
  auto& singlentity = world.GetSinglenity();
  ett_pool_.Release(singlentity);
  auto& cworld = reinterpret_cast<const World&>(world);
  pool_.Release(cworld);
}

WorldPool::size_type WorldPool::SizeImpl() const noexcept {
  return pool_.Size();
}

}  // namespace internal
}  // namespace einu