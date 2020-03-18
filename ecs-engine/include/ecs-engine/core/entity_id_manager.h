#pragma once

#include <atomic>

#include "ecs-engine/core/entity_id.h"

namespace ecs {

class EntityIDManager {
 public:
  using size_type = std::size_t;

  EntityID GenEntityID() noexcept;

 private:
  std::atomic<size_type> free_id_{0};
};

//////////////////////////////////////////////////////////////////////////

inline EntityID EntityIDManager::GenEntityID() noexcept {
  return EntityID{free_id_++};
}

}  // namespace ecs

