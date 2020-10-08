#pragma once

#include <einu-tmp/type_list.h>

#include "einu-core/xnent.h"

namespace einu {

template <typename... Components>
using XnentList = tmp::TypeList<Components...>;

}  // namespace einu