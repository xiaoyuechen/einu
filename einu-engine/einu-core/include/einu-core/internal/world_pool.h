#pragma once

#include <einu-util/object_pool.h>

#include "einu-core/i_entity_pool.h"
#include "einu-core/i_world_pool.h"
#include "einu-core/internal/world.h"

namespace einu {
namespace internal {

class WorldPool : public IWorldPool {
 public:
  WorldPool(IEntityPool& ett_pool) {}

 private:
  using Pool = util::DynamicPool<World>;

  void SetPolicyImpl(const Policy& policy) override;
  IWorld& AcquireImpl() override;
  void ReleaseImpl(const IWorld& world) override;
  size_type SizeImpl() const noexcept override;

  Pool pool_;
};

}  // namespace internal
}  // namespace einu