#include "ecs-core/manager/Entity_manager.h"

namespace ecs {
Entity_id Entity_manager::spawn_entity() {
  return id_manager_.create_entity();
}

Component_manager_admin& Entity_manager::get_component_admin() { return comp_admin_; }

Component_mask_manager& Entity_manager::get_component_mask_manager() {
  return comp_mask_manager_;
}
}  // namespace ecs