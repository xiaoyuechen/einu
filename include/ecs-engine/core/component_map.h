#pragma once

#include "einu-engine/core/i_component.h"
#include "einu-engine/utility/container/linear_search_map.h"
#include "einu-engine/utility/rtti/class_index.h"

namespace einu {
using ComponentMap = LinearSearchMap<rtti::TypeID, Xnent*>;
}  // namespace einu
