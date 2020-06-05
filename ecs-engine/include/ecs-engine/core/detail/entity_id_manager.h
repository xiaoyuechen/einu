#pragma once

#include <atomic>

#include "ecs-engine/core/entity_id.h"

namespace ecs {
namespace detail {

class EntityIDManager {
 public:
  using size_type = std::size_t;

  EntityID GenEntityID() noexcept { return EntityID{free_id_++}; }

 private:
  std::atomic<size_type> free_id_{0};
};

}  // namespace detail
}  // namespace ecs