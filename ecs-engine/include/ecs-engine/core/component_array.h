#pragma once

#include <array>

#include "ecs-engine/core/component_setting.h"
#include "ecs-engine/core/i_component.h"
#include "ecs-engine/utility/rtti/class_index.h"

namespace ecs {

using ComponentSet = std::map<rtti::ClassIndex, IComponent*>;

template <typename ComponentSetting>
class ComponentArray {
 public:
  template <typename T>
  void Insert(T& component) noexcept;
  template <typename T>
  void Erase() noexcept;

  template <typename T>
  const T& Get() const noexcept;
  template <typename T>
  T& Get() noexcept;
  template <typename T>
  bool Has() const noexcept;

 private:
  static constexpr auto kComponentTypeCount =
      ComponentSetting::GetComponentTypeCount();
  std::array<IComponent*, kComponentTypeCount> arr_{nullptr};
};

//////////////////////////////////////////////////////////////////////////

template <typename ComponentSetting>
template <typename T>
inline void ComponentArray<ComponentSetting>::Insert(T& component) noexcept {
  auto constexpr index = ComponentSetting::template GetComponentTypeIndex<T>();
  arr_[index] = &component;
}

template <typename ComponentSetting>
template <typename T>
inline void ComponentArray<ComponentSetting>::Erase() noexcept {
  constexpr auto index = ComponentSetting::template GetComponentTypeIndex<T>();
  arr_[index] = nullptr;
}

template <typename ComponentSetting>
template <typename T>
inline const T& ComponentArray<ComponentSetting>::Get() const noexcept {
  constexpr auto index = ComponentSetting::template GetComponentTypeIndex<T>();
  return reinterpret_cast<const T&>(*arr_[index]);
}

template <typename ComponentSetting>
template <typename T>
inline T& ComponentArray<ComponentSetting>::Get() noexcept {
  return const_cast<T&>(static_cast<const ComponentArray&>(*this).Get<T>());
}

template <typename ComponentSetting>
template <typename T>
inline bool ComponentArray<ComponentSetting>::Has() const noexcept {
  constexpr auto index = ComponentSetting::template GetComponentTypeIndex<T>();
  return arr_[index] != nullptr;
}

}  // namespace ecs
