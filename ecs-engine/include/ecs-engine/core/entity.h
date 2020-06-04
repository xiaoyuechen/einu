#pragma once

#include "ecs-engine/core/component_array.h"
#include "ecs-engine/core/component_setting.h"
#include "ecs-engine/core/entity_id.h"
#include "ecs-engine/utility/rtti/class_index.h"

namespace ecs {

template <typename ComponentMaskType, typename ThreadingModel>
class Entity_N : public ThreadingModel {
 public:
  using ComponentMask = ComponentMaskType;
  using ComponentMap = std::map<rtti::ClassIndex, IComponent&>;

  Entity_N(EntityID eid) { eid_ = eid; }

  void AddComponent(rtti::ClassIndex idx, IComponent& comp) {
    typename ThreadingModel::Lock lock(*this);
    mask_[idx] = true;
    map_[idx] = comp;
  }

  void RemoveComponent(rtti::ClassIndex idx) {
    typename ThreadingModel::Lock lock(*this);
    mask_[idx] = false;
    map_.erase(idx);
  }

  const IComponent& GetComponent(rtti::ClassIndex idx) const {
    return map_.at(idx);
  }
  IComponent& GetComponent(rtti::ClassIndex idx) { return map_.at(idx); }

  EntityID GetEntityID() const { return eid_; }
  const ComponentMask& GetComponentMask() const { return mask_; }
  const ComponentMap& GetComponentMap() const { return map_; }

 private:
  EntityID eid_;
  ComponentMask mask_;
  ComponentMap map_;
};

template <typename ComponentSetting>
class Entity {
 public:
  using ComponentMask = typename ComponentSetting::ComponentMask;
  using ComponentArray = ComponentArray<ComponentSetting>;

  template <typename T>
  void AddComponent(T& comp) noexcept;
  template <typename T>
  void RemoveComponent() noexcept;
  template <typename T>
  const T& GetComponent() const noexcept;
  template <typename T>
  T& GetComponent() noexcept;
  template <typename T>
  bool HasComponent() const noexcept;

  const ComponentMask& GetComponentMask() const noexcept;
  const ComponentArray& GetComponentArray() const noexcept;

 private:
  ComponentMask mask_ = ComponentSetting::template GetComponentMask<>();
  ComponentArray comp_arr_{};
};

//////////////////////////////////////////////////////////////////////////

template <typename ComponentSetting>
template <typename T>
inline void Entity<ComponentSetting>::AddComponent(T& comp) noexcept {
  comp_arr_.Insert(comp);
  mask_[ComponentSetting::template GetComponentTypeIndex<T>()] = true;
}

template <typename ComponentSetting>
template <typename T>
inline void Entity<ComponentSetting>::RemoveComponent() noexcept {
  comp_arr_.Erase<T>();
  mask_[ComponentSetting::template GetComponentTypeIndex<T>()] = false;
}

template <typename ComponentSetting>
template <typename T>
inline const T& Entity<ComponentSetting>::GetComponent() const noexcept {
  return comp_arr_.Get<T>();
}

template <typename ComponentSetting>
template <typename T>
inline T& Entity<ComponentSetting>::GetComponent() noexcept {
  return comp_arr_.Get<T>();
}

template <typename ComponentSetting>
template <typename T>
inline bool Entity<ComponentSetting>::HasComponent() const noexcept {
  return comp_arr_.Has<T>();
}

template <typename ComponentSetting>
inline const typename Entity<ComponentSetting>::ComponentMask&
Entity<ComponentSetting>::GetComponentMask() const noexcept {
  return mask_;
}

template <typename ComponentSetting>
inline const typename Entity<ComponentSetting>::ComponentArray&
Entity<ComponentSetting>::GetComponentArray() const noexcept {
  return comp_arr_;
}

}  // namespace ecs
