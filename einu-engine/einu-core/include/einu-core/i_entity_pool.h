#pragma once

#include "einu-core/i_entity.h"
#include "einu-core/pool_policy.h"

namespace einu {

class IEntityPool {
 public:
  using Policy = PoolPolicy<>;

  virtual ~IEntityPool() = default;

  void SetPolicy(const Policy& policy) { SetPolicyImpl(policy); }
  IEntity& Acquire() { return AcquireImpl(); }
  void Release(const IEntity& ett) { ReleaseImpl(ett); }

 private:
  virtual void SetPolicyImpl(const Policy& policy) = 0;
  virtual IEntity& AcquireImpl() = 0;
  virtual void ReleaseImpl(const IEntity& ett) = 0;
};

}  // namespace einu