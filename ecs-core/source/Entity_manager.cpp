#include "ecs-core/manager/Entity_manager.h"

namespace ecs {
Entity_manager::Entity_handle::Entity_handle(const Entity_id& e, Entity_manager& m)
    : entity_(e)
    , manager_(m) {}

typename Entity_manager::Entity_handle Entity_manager::spawn_entity() {
  auto e = id_manager_.create_entity();
  return Entity_handle(e, *this);
}

Component_admin& Entity_manager::get_component_admin() { return comp_admin_; }

Component_mask_manager& Entity_manager::get_component_mask_manager() {
  return comp_mask_manager_;
}
}  // namespace ecs