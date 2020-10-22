#pragma once

#include "einu-core/xnent_list.h"

namespace einu {

template <typename ComponentList, typename SinglenentList>
struct NeedList;

template <typename... Components, typename... Singlenents>
struct NeedList<XnentList<Components...>, XnentList<Singlenents...>> {
  using ComponentList = XnentList<Components...>;
  using SinglenentList = XnentList<Singlenents...>;
};

}  // namespace einu