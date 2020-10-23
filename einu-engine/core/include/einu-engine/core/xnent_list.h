#pragma once

#include <einu-engine/core/tmp/type_list.h>

#include <type_traits>

#include "einu-engine/core/xnent.h"

namespace einu {

template <typename... Xnents>
struct XnentList {
  static_assert((std::is_base_of<Xnent, Xnents>::value && ...) &&
                "must be subtype of Xnent");
};

template <typename XnentList>
struct ToTypeList;

template <typename... Xnents>
struct ToTypeList<XnentList<Xnents...>> {
  using Type = tmp::TypeList<Xnents...>;
};

// tmp::TypeList<Components...>;

}  // namespace einu