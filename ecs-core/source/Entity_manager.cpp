#include "ecs-core/manager/Entity_manager.h"

namespace ecs {
EntityManager::Handle::Handle(const Entity& e, EntityManager& m)
    : entity_(e)
    , manager_(m) {}

typename EntityManager::Handle EntityManager::spawn_entity() {
  auto e = id_manager_.create_entity();
  return Handle(e, *this);
}
}  // namespace ecs