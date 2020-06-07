#pragma once

#include <tuple>

#include "ecs-engine/core/component_context.h"
#include "ecs-engine/utility/algorithm.h"

namespace ecs {

template <typename EntityManager>
class IEntityPrototype {
 public:
  virtual ~IEntityPrototype() = default;
  virtual typename EntityManager::EntityHandle CloneEntity(
      EntityManager& ett_mgr) const = 0;
};

template <typename EntityManager, typename RequiredComponentList>
class EntityPrototype;

template <typename EntityManager, typename... Ts>
class EntityPrototype<EntityManager, ComponentList<Ts...>>
    : public IEntityPrototype<EntityManager> {
 public:
  virtual typename EntityManager::EntityHandle CloneEntity(
      EntityManager& ett_mgr) const override {
    auto handle = ett_mgr.CreateEntity();
    auto f = [&](auto i) {
      auto& comp =
          handle.AddComponent<std::tuple_element<i, ComponentTuple>::type>();
      comp = std::get<i>(comp_tup_);
    };
    algo::StaticFor<sizeof...(Ts)>(f);
    return handle;
  }

  template <typename T>
  const T& GetComponent() const {
    return std::get<T>(comp_tup_);
  }

  template <typename T>
  T& GetComponent() {
    return std::get<T>(comp_tup_);
  }

 private:
  using ComponentTuple = std::tuple<Ts...>;
  ComponentTuple comp_tup_;
};

}  // namespace ecs
