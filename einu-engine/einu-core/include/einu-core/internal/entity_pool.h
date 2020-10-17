#pragma once

#include <einu-util/object_pool.h>

#include <atomic>

#include "einu-core/i_entity_pool.h"
#include "einu-core/internal/entity.h"
#include "einu-core/internal/xnent_mask.h"

namespace einu {
namespace internal {

class SimpleEIDManager {
 public:
  EID Acquire() noexcept { return available_++; }
  void Release(EID id) noexcept {}

 private:
  std::atomic_uint64_t available_ = 0;
};

template <std::size_t max_comp, typename EIDManager>
class EntityPool final : public IEntityPool {
 private:
  void SetPolicyImpl(const Policy& policy) override {
    pool_.SetGrowth(policy.growth_func);
    pool_.GrowExtra(policy.init_size);
  }

  IEntity& AcquireImpl() override {
    auto&& [ett, mask, table] = pool_.Acquire();
    mask.reset();
    table.fill(nullptr);
    ett = Entity(~EID{0}, mask, table);
    return ett;
  }

  void ReleaseImpl(const IEntity& ett) noexcept override {
    auto& entity = static_cast<const Entity&>(ett);
    pool_.Release(std::forward_as_tuple(entity, *entity.mask, *entity.table));
  }

  size_type SizeImpl() const noexcept override { return pool_.Size(); }

  using Entity = Entity<max_comp>;
  using ComponentMask = StaticXnentMask<max_comp>;
  using ComponentTable = StaticComponentTable<max_comp>;
  using Pool = util::DynamicPool<Entity, ComponentMask, ComponentTable>;

  Pool pool_;
};

}  // namespace internal
}  // namespace einu