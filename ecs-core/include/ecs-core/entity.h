#ifndef ENTITY_H_
#define ENTITY_H_

#include "ecs-core/component_array.h"
#include "ecs-core/component_setting.h"

namespace ecs {

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
  mask_[ComponentSetting::template GetComponentTypeIndex<T>()] = true;
  comp_arr_.Insert(comp);
}

template <typename ComponentSetting>
template <typename T>
inline void Entity<ComponentSetting>::RemoveComponent() noexcept {
  mask_[ComponentSetting::template GetComponentTypeIndex<T>()] = false;
  comp_arr_.Erase<T>();
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

#endif  // ENTITY_H_