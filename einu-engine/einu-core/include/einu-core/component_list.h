#pragma once

#include <einu-tmp/type_list.h>

#include "einu-core/i_component.h"

namespace einu {

template <typename... Components>
using ComponentList = tmp::TypeList<Components...>;

}  // namespace einu