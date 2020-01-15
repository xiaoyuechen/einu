#pragma once
#include <map>
#include <vector>
#include <memory>
#include "ecs-core/manager/Component_manager.h"
#include "ecs-core/manager/Entity_manager.h"
#include "ecs-core/system/I_system.h"

namespace ecs {
class World {
 public:
  template <typename S, typename... Args>
  void add_system(Args&&... args);



 private:
  using Sys_ptr = std::unique_ptr<I_system>;
  std::vector<Sys_ptr> system_arr_;
  EntityManager entity_manager_;
};
}  // namespace ecs

namespace ecs {
template <typename S, typename... Args>
inline void World::add_system(Args&&... args) {
  auto s = std::make_unique<S>(std::forward<Args>(args)...);
  system_arr_.push_back(std::move(s));
}
}  // namespace ecs