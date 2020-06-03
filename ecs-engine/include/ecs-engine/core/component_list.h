#pragma once

#include "ecs-engine/core/component.h"
#include "ecs-engine/utility/tmp/type_list.h"

namespace ecs {

template <typename... Ts>
struct ComponentList : public tmp::TypeList<Ts...> {
  // TODO(Xiaoyue Chen): Static assert IComponent is base of types
};

}  // namespace ecs
