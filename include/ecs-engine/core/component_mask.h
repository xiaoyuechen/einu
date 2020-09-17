#pragma once

#include <bitset>
#include <cassert>
#include <type_traits>

#include "ecs-engine/core/i_component.h"
#include "ecs-engine/utility/rtti/class_index_storage.h"

namespace ecs {

static constexpr std::size_t kMaxComponentCount = 256;
using ComponentMask = std::bitset<kMaxComponentCount>;

}  // namespace ecs