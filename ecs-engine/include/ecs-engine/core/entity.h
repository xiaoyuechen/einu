#pragma once

#include <map>

#include "ecs-engine/core/detail/component_mask.h"
#include "ecs-engine/core/entity_id.h"
#include "ecs-engine/core/i_component.h"
#include "ecs-engine/utility/rtti/class_index.h"

namespace ecs {

class Entity {
 public:
  using ComponentMap = std::map<rtti::ClassIndex, IComponent&>;

  Entity(EntityID eid = EntityID{}) { eid_ = eid; }

  template <typename T>
  void AddComponent(T& comp) {
    auto idx = rtti::GetClassIndex<T>();
    AddComponent(idx, comp);
  }

  template <typename T>
  void RemoveComponent() {
    auto idx = rtti::GetClassIndex<T>();
    RemoveComponent(idx);
  }

  void AddComponent(rtti::ClassIndex idx, IComponent& comp) {
    mask_[idx] = true;
    map_.insert({idx, comp});
  }

  void RemoveComponent(rtti::ClassIndex idx) {
    mask_[idx] = false;
    map_.erase(idx);
  }

  const IComponent& GetComponent(rtti::ClassIndex idx) const {
    return map_.at(idx);
  }
  IComponent& GetComponent(rtti::ClassIndex idx) { return map_.at(idx); }

  void SetEntityID(EntityID eid) noexcept { eid_ = eid; }
  EntityID GetEntityID() const noexcept { return eid_; }
  const detail::ComponentMask& GetComponentMask() const noexcept {
    return mask_;
  }
  const ComponentMap& GetComponentMap() const noexcept { return map_; }

  std::size_t GetComponentCount() const noexcept { return map_.size(); }

 private:
  EntityID eid_;
  detail::ComponentMask mask_;
  ComponentMap map_;
};

}  // namespace ecs
