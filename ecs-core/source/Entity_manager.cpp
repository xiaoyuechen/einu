#include "ecs-core/manager/Entity_manager.h"

namespace ecs {
Entity_manager::Handle::Handle(const Entity& e, Entity_manager& m)
    : entity_(e)
    , manager_(m) {}

Entity_manager::Entity_manager(std::unique_ptr<Component_admin> comp_admin)
    : comp_admin_(std::move(comp_admin)) {}

typename Entity_manager::Handle Entity_manager::spawn_entity() {
  auto e = id_manager_.create_entity();
  return Handle(e, *this);
}
}  // namespace ecs