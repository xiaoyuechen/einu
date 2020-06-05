#pragma once

#include "ecs-engine/core/entity_id.h"

namespace ecs {

template <typename EntityManager>
class EntityHandle {
 public:
  EntityHandle(EntityID eid, EntityManager& ett_mgr)
      : eid_(eid)
      , ett_mgr_(ett_mgr) {}

  template <typename T>
  T& AddComponent() {
    return ett_mgr_.AddComponent<T>(eid_);
  }

  template <typename T>
  void RemoveComponent() {
    ett_mgr_.RemoveComponent<T>(eid_);
  }

  template <typename T>
  const T& GetComponent() const {
    return ett_mgr_.GetComponent<T>(eid_);
  }

  template <typename T>
  T& GetComponent() {
    return ett_mgr_.GetComponent<T>(eid_);
  }

  const EntityID& GetEntityID() const noexcept { return eid_; }

  void Destory() { ett_mgr_.DestroyEntity(eid_); }

 private:
  EntityID eid_;
  EntityManager& ett_mgr_;
};

}  // namespace ecs