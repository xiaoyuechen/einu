#pragma once

#include <bitset>
#include <cassert>
#include <type_traits>

#include "einu-engine/core/i_component.h"
#include "einu-engine/utility/rtti/class_index_storage.h"

namespace einu {

static constexpr std::size_t kMaxComponentCount = 256;
using XnentMask = std::bitset<kMaxComponentCount>;

}  // namespace einu