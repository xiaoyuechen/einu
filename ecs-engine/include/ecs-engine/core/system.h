#pragma once

#include <tuple>
#include <vector>

#include "ecs-engine/core/component_context.h"
#include "ecs-engine/core/entity_manager.h"

namespace ecs {

template <typename EntityManager, typename RequiredComponentList>
class System;

template <typename EntityManager, typename... Ts>
class System<EntityManager, ComponentList<Ts...>> {
 public:
  using ComponentTuple = std::tuple<Ts&...>;
  using ComponentTupleBuffer = std::vector<ComponentTuple>;
  using EIDs = std::vector<EntityID>;

  System(EntityManager& ett_mgr)
      : ett_mgr_(ett_mgr) {
    ett_mgr_.RegisterInterest<Ts...>();
  }

  const ComponentTupleBuffer& GetMatchingComponentTuples() const {
    matching_comps_.clear();
    eid_arr_.clear();
    ett_mgr_.GetMatchingComponentsEids(&matching_comps_, &eid_arr_);
    return matching_comps_;
  }

  ComponentTupleBuffer& GetMatchingComponentTuples() {
    return const_cast<ComponentTupleBuffer&>(
        static_cast<const System&>(*this).GetMatchingComponentTuples());
  }

  const typename EntityManager::EntityHandle GetEntityHandle(
      const ComponentTuple& tuple) const {
    const auto& eid = GetEntityID(tuple);
    return EntityManager::EntityHandle(eid, ett_mgr_);
  }

  typename EntityManager::EntityHandle GetEntityHandle(
      const ComponentTuple& tuple) {
    const auto handle =
        static_cast<const System&>(*this).GetEntityHandle(tuple);
    return *const_cast<typename EntityManager::EntityHandle*>(&handle);
  }

  EntityID GetEntityID(const ComponentTuple& tuple) const {
    auto index = &tuple - matching_comps_.data();
    return eid_arr_[index];
  }

  const EIDs& GetEntityIDs() const noexcept { return eid_arr_; }

  const EntityManager& GetEntityManager() const { return ett_mgr_; }
  EntityManager& GetEntityManager() {
    return const_cast<EntityManager&>(
        static_cast<const System&>(*this).GetEntityManager());
  }

 private:
  EntityManager& ett_mgr_;
  mutable ComponentTupleBuffer matching_comps_;
  mutable EIDs eid_arr_;
};

}  // namespace ecs