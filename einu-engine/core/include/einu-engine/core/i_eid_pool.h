#pragma once

#include "einu-engine/core/eid.h"

namespace einu {

class IEIDPool {
 public:
  virtual ~IEIDPool() = default;

  EID Acquire() noexcept { return AcquireImpl(); }

  void Release(EID eid) noexcept { ReleaseImpl(eid); }

 private:
  virtual EID AcquireImpl() noexcept = 0;
  virtual void ReleaseImpl(EID eid) noexcept = 0;
};

}  // namespace einu
