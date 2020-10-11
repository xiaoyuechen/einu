#pragma once

#include "einu-core/i_entity_pool.h"
#include "einu-core/internal/entity.h"
#include "einu-core/internal/xnent_mask.h"

namespace einu {
namespace internal {

class EntityPool final : public IEntityPool {
 public:
 private:
  void SetPolicyImpl(const Policy& policy) override {}

  IEntity& AcquireImpl() override {
    throw std::logic_error("The method or operation is not implemented.");
  }

  void ReleaseImpl(const IEntity& ett) override {
    throw std::logic_error("The method or operation is not implemented.");
  }
};

}  // namespace internal
}  // namespace einu