#pragma once
#include <atomic>
#include "ecs-core/entity/Entity_id.h"

namespace ecs {
class Entity_id_manager {
 public:
  using size_type = std::size_t;

 public:
  Entity_id create_entity();

 private:
  std::atomic<size_type> free_id_{0};
};
}  // namespace ecs

namespace ecs {
inline Entity_id Entity_id_manager::create_entity() {
  return Entity_id{free_id_++};
}
}  // namespace ecs