#pragma once

#include "einu-core/i_entity.h"

namespace einu {

class IEntityPool {
 public:
  virtual ~IEntityPool() = default;
  virtual IEntity& Acquire() = 0;
  virtual void Release(const IEntity& ett) = 0;
};

}  // namespace einu