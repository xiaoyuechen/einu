#pragma once
#include "ecs-core/manager/Component_manager.h"
#include "ecs-core/component/Component_type.h"

namespace ecs {
class Component_admin {
 private:
  using Component_manager_map =
      std::map<Component_type, std::unique_ptr<I_component_manager>>;
};
}