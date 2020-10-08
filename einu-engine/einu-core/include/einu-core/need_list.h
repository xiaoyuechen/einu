#pragma once

#include "einu-core/component_list.h"
#include "einu-core/singlenent_list.h"

namespace einu {

template <typename ComponentList, typename SinglenentList>
struct NeedList;

template <typename... Components, typename... Singlenents>
struct NeedList<ComponentList<Components...>, SinglenentList<Singlenents...>> {
  using ComponentList = ComponentList<Components...>;
  using SinglenentList = SinglenentList<Singlenents...>;
};

}  // namespace einu