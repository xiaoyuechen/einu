#pragma once

#include <atomic>

#include "einu-engine/core/i_eid_pool.h"

namespace einu {
namespace internal {

class EIDPool final : public IEIDPool {
 private:
  EID AcquireImpl() noexcept override { return available_++; }

  void ReleaseImpl(EID eid) noexcept override {}

  std::atomic_uint32_t available_{0};
};

}  // namespace internal
}  // namespace einu
