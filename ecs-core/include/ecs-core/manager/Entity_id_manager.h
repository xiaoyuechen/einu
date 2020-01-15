#pragma once
#include <atomic>
#include "ecs-core/entity/Entity.h"

namespace ecs {
class Entity_id_manager {
 public:
  using size_type = std::size_t;

 public:
  Entity create_entity();

 private:
  std::atomic<size_type> free_entity{0};
};
}  // namespace ecs

namespace ecs {
inline Entity Entity_id_manager::create_entity() {
  return Entity{free_entity++};
}
}  // namespace ecs