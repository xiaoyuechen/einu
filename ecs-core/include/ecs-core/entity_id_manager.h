#ifndef ENTITY_ID_MANAGER_H_
#define ENTITY_ID_MANAGER_H_

#include <atomic>

#include "ecs-core/entity_id.h"

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

#endif  // ENTITY_ID_MANAGER_H_