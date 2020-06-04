#pragma once

#include <bitset>

#include "ecs-engine/core/component_list.h"
#include "ecs-engine/utility/rtti/class_index.h"
#include "ecs-engine/utility/rtti/class_index_register.h"

namespace ecs {


template <typename ComponentList, typename SingletonComponentList>
struct ComponentSetting {
  using Components = typename ComponentList::TypeList;
  using SingletonComponents = typename SingletonComponentList::TypeList;

  static constexpr std::size_t GetComponentTypeCount();

  using ComponentMask = std::bitset<GetComponentTypeCount()>;
  using ComponentTypeIndex = std::size_t;

  template <typename T>
  static constexpr ComponentTypeIndex GetComponentTypeIndex();

  template <typename... Ts>
  static ComponentMask GetComponentMask();

  template <ComponentTypeIndex index>
  using ComponentTypeAt = typename tmp::TypeAt<Components, index>::Type;
};

//////////////////////////////////////////////////////////////////////////

template <typename ComponentList, typename SingletonComponentList>
inline constexpr std::size_t ComponentSetting<
    ComponentList, SingletonComponentList>::GetComponentTypeCount() {
  return tmp::Size<Components>::value;
}

template <typename ComponentList, typename SingletonComponentList>
template <typename T>
inline constexpr
    typename ComponentSetting<ComponentList,
                              SingletonComponentList>::ComponentTypeIndex
    ComponentSetting<ComponentList,
                     SingletonComponentList>::GetComponentTypeIndex() {
  return tmp::IndexOf<Components, std::remove_const<T>::type>::value;
}

template <typename ComponentList, typename SingletonComponentList>
template <typename... Ts>
typename ComponentSetting<ComponentList, SingletonComponentList>::ComponentMask
ComponentSetting<ComponentList, SingletonComponentList>::GetComponentMask() {
  ComponentMask mask;
  (mask.set(GetComponentTypeIndex<Ts>()), ...);
  return mask;
}

}  // namespace ecs