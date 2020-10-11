#pragma once

#include "einu-core/i_entity.h"

namespace einu {

class IEntityPool {
 public:
  virtual ~IEntityPool() = default;

  IEntity& Acquire() { return AcquireImpl(); }
  void Release(const IEntity& ett) { ReleaseImpl(); }

 private:
  virtual IEntity& AcquireImpl() = 0;
  virtual void ReleaseImpl(const IEntity& ett) = 0;
};

}  // namespace einu