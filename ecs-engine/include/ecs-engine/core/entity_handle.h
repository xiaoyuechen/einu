#pragma once

#include "ecs-engine/core/entity_data.h"
#include "ecs-engine/utility/rtti/class_index.h"

namespace ecs {

class ConstEntityHandle {
 public:
  ConstEntityHandle(const EntityData& ett)
      : ett_(ett) {}

  template <typename T>
  const T& GetComponent() const {
    return static_cast<const T&>(ett_.GetComponent(rtti::GetClassIndex<T>()));
  }

  const EntityID& GetEntityID() const noexcept { return ett_.GetEntityID(); }

 private:
  const EntityData& ett_;
};

template <typename EntityManager>
class EntityHandle {
 public:
  EntityHandle(EntityData& ett, EntityManager& ett_mgr)
      : ett_(ett)
      , ett_mgr_(ett_mgr) {}

  template <typename T>
  T& AddComponent() {
    return ett_mgr_.AddComponent<T>(ett_);
  }

  template <typename T>
  void RemoveComponent() {
    ett_mgr_.RemoveComponent<T>(ett_);
  }

  template <typename T>
  const T& GetComponent() const {
    return static_cast<const T&>(ett_.GetComponent(rtti::GetClassIndex<T>()));
  }

  template <typename T>
  T& GetComponent() {
    return static_cast<T&>(ett_.GetComponent(rtti::GetClassIndex<T>()));
  }

  const EntityID& GetEntityID() const noexcept { return ett_.GetEntityID(); }

  void Destory() { ett_mgr_.DestroyEntity(ett_); }

 private:
  EntityData& ett_;
  EntityManager& ett_mgr_;
};

}  // namespace ecs