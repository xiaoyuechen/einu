#pragma once

#include <bitset>
#include <cstddef>
#include <unordered_map>

#include "einu-core/i_entity.h"

namespace einu {
namespace internal {

template <std::size_t max_comp_count>
class Entity : public IEntity {
 public:
  EID GetID() const noexcept override { return eid_; }

 private:
  using Signature = std::bitset<max_comp_count>;
  using SignatureTable =
      std::unordered_map<const internal::ComponentIndexList*, Signature>;

  static SignatureTable& GetSignatureTable() {
    static Signature& table = *new SignatureTable{};
    return table;
  }

  bool HasComponents(const internal::ComponentIndexList& idx_list)
      const noexcept override final {
    throw std::logic_error("The method or operation is not implemented.");
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
  Signature signature_{};
};

}  // namespace internal
}  // namespace einu