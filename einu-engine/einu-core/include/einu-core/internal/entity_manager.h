#pragma once

#include "einu-core/i_entity_manager.h"

namespace einu {
namespace internal {

template <std::size_t max_comp>
using StaticComponentTable = std::array<Xnent*, max_comp>;

template <std::size_t max_comp>
class Entity {
 public:
  using StaticXnentMask = StaticXnentMask<max_comp>;
  using ComponentTable = StaticComponentTable<max_comp>;

  Entity() noexcept = default;
  Entity(EID id, StaticXnentMask& mask, ComponentTable& table) noexcept
      : id_(id)
      , mask_(&mask)
      , table_(&table) {}

  const StaticXnentMask& Mask() const noexcept { return *mask_; }
  StaticXnentMask& Mask() noexcept { return *mask_; }
  const ComponentTable& Table() const noexcept { return *table_; }
  ComponentTable& Table() noexcept { return *table_; }

 private:
  EID GetIDImpl() const noexcept override { return id_; }

  void ResetImpl() noexcept override {
    id_ = ~EID{0};
    Mask().reset();
  }

  bool HasComponentsImpl(const DynamicXnentMask& mask) const noexcept override {
    return (mask & Mask()) == mask;
  }

  const Xnent& GetComponentImpl(XnentTypeID idx) const noexcept override {
    return *Table()[idx];
  }

  Xnent& GetComponentImpl(XnentTypeID idx) noexcept override {
    return *Table()[idx];
  }

  void AddComponentImpl(XnentTypeID idx, Xnent& comp) override {
    assert(!Mask()[idx] && "already have component");
    Table()[idx] = &comp;
    Mask()[idx] = true;
  }

  Xnent& RemoveComponentImpl(XnentTypeID idx) noexcept override {
    assert(Mask()[idx] && "do not have component");
    Mask()[idx] = false;
    auto& tmp = *Table()[idx];
    Table()[idx] = nullptr;
    return tmp;
  }

  EID id_ = ~EID{0};
  StaticXnentMask* mask_ = nullptr;
  ComponentTable* table_ = nullptr;
};

template <std::size_t max_comp>
class EntityManager : public IEntityManager {
 private:
  using ComponentMask = StaticXnentMask<max_comp>;
  using ComponentTable = StaticComponentTable<max_comp>;
  using Pool = util::DynamicPool<ComponentMask, ComponentTable>;

  EID CreateEntityImpl() override {
    throw std::logic_error("The method or operation is not implemented.");
  }

  void DestroyEntityImpl(EID eid) noexcept override {
    throw std::logic_error("The method or operation is not implemented.");
  }

  Xnent& AddComponentImpl(EID eid, XnentTypeID tid) override {
    throw std::logic_error("The method or operation is not implemented.");
  }

  void RemoveComponentImpl(EID eid, XnentTypeID tid) noexcept override {
    throw std::logic_error("The method or operation is not implemented.");
  }

  Xnent& GetComponentImpl(EID eid, XnentTypeID tid) noexcept override {
    throw std::logic_error("The method or operation is not implemented.");
  }

  const Xnent& GetComponentImpl(EID eid,
                                XnentTypeID tid) const noexcept override {
    throw std::logic_error("The method or operation is not implemented.");
  }

  void GetEntitiesWithComponentsImpl(
      EntityBuffer& buffer, const internal::DynamicXnentMask& mask) override {
    throw std::logic_error("The method or operation is not implemented.");
  }

  void Reset() override noexcept {
    throw std::logic_error("The method or operation is not implemented.");
  }
};

}  // namespace internal
}  // namespace einu