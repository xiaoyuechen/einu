#pragma once

#include <cstdint>

#include "einu-core/i_entity.h"
#include "einu-core/pool_policy.h"

namespace einu {

class IEntityPool {
 public:
  using size_type = std::size_t;
  using Policy = PoolPolicy<>;

  virtual ~IEntityPool() = default;

  void SetPolicy(const Policy& policy) { SetPolicyImpl(policy); }
  IEntity& Acquire() { return AcquireImpl(); }
  void Release(const IEntity& ett) noexcept { ReleaseImpl(ett); }
  size_type Size() const noexcept { return SizeImpl(); }

 private:
  virtual void SetPolicyImpl(const Policy& policy) = 0;
  virtual IEntity& AcquireImpl() = 0;
  virtual void ReleaseImpl(const IEntity& ett) noexcept = 0;
  virtual size_type SizeImpl() const noexcept = 0;
};

}  // namespace einu