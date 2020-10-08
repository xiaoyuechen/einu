#pragma once

#include <array>
#include <bitset>
#include <cstddef>

#include "einu-core/i_entity.h"

namespace einu {
namespace internal {

template <std::size_t max_comp>
class Entity : public IEntity {
 public:
  Entity(EID eid, StaticXnentMask& mask) {}

  EID GetID() const noexcept override { return eid_; }

 private:
  using StaticComponentSignature = StaticComponentSignature<max_comp>;

  bool HasComponents(
      const internal::XnentMask& mask) const noexcept override final {
    return mask & mask_ == mask_;
  }

  const Xnent& GetComponent(
      internal::XnentIndex idx) const noexcept override {
    throw std::logic_error("The method or operation is not implemented.");
  }

  Xnent& GetComponent(internal::XnentIndex idx) noexcept override {
    throw std::logic_error("The method or operation is not implemented.");
  }

  void AddComponent(internal::XnentIndex idx, Xnent& comp) override {
    throw std::logic_error("The method or operation is not implemented.");
  }

  Xnent& RemoveComponent(internal::XnentIndex idx) noexcept override {
    throw std::logic_error("The method or operation is not implemented.");
  }

  EID eid_ = ~EID{0};
  StaticComponentSignature& mask_{};
};

}  // namespace internal
}  // namespace einu