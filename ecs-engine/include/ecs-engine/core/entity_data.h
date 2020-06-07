#pragma once

#include <map>

#include "ecs-engine/core/detail/component_mask.h"
#include "ecs-engine/core/entity_id.h"
#include "ecs-engine/core/i_component.h"
#include "ecs-engine/utility/rtti/class_index.h"

namespace ecs {

class EntityData {
 public:
  using ComponentMap = std::map<rtti::ClassIndex, IComponent&>;

  EntityData(EntityID eid = EntityID{}) { eid_ = eid; }

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

  bool HasComponent(rtti::ClassIndex idx) const { return mask_.test(idx); }

  void SetEntityID(EntityID eid) noexcept { eid_ = eid; }
  EntityID GetEntityID() const noexcept { return eid_; }

  const detail::ComponentMask& GetComponentMask() const noexcept {
    return mask_;
  }

  std::size_t GetComponentCount() const noexcept { return map_.size(); }

  void Activate() noexcept { is_active_ = true; }
  bool IsActive() const noexcept { return is_active_; }

 private:
  EntityID eid_;
  detail::ComponentMask mask_;
  ComponentMap map_;
  bool is_active_ = false;
};

inline bool operator==(const EntityData& lhs, const EntityData& rhs) noexcept {
  return lhs.GetEntityID() == rhs.GetEntityID();
}

inline bool operator!=(const EntityData& lhs, const EntityData& rhs) noexcept {
  return !(lhs == rhs);
}

}  // namespace ecs
