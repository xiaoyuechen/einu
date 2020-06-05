#pragma once

#include <bitset>
#include <cassert>
#include <type_traits>

#include "ecs-engine/core/i_component.h"
#include "ecs-engine/utility/rtti/class_index.h"

namespace ecs {
namespace detail {

static constexpr std::size_t kMaxComponentCount = 256;
using ComponentMask = std::bitset<kMaxComponentCount>;

template <typename... Ts>
const ComponentMask& GetComponentMaskStatic() {
  static_assert((std::is_base_of<IComponent, Ts>::value && ...),
                "<IComponent> must be the base class of all the <Ts>");
  static ComponentMask mask;
  (mask.set(rtti::GetClassIndex<Ts>()), ...);
  return mask;
}

}  // namespace detail
}  // namespace ecs