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
  EID GetID() const noexcept override { return eid_; }

 private:
  using StaticComponentSignature = StaticComponentSignature<max_comp>;

  bool HasComponents(
      const internal::ComponentMask& sig) const noexcept override final {
    return sig & signature_ == signature_;
  }

  const IComponent& GetComponent(
      internal::ComponentIndex idx) const noexcept override {
    throw std::logic_error("The method or operation is not implemented.");
  }

  IComponent& GetComponent(internal::ComponentIndex idx) noexcept override {
    throw std::logic_error("The method or operation is not implemented.");
  }

  void AddComponent(internal::ComponentIndex idx, IComponent& comp) override {
    throw std::logic_error("The method or operation is not implemented.");
  }

  IComponent& RemoveComponent(internal::ComponentIndex idx) noexcept override {
    throw std::logic_error("The method or operation is not implemented.");
  }

  EID eid_ = ~EID{0};
  StaticComponentSignature signature_{};
};

}  // namespace internal
}  // namespace einu