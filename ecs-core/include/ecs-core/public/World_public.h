#pragma once
#include "ecs-core/I_system.h"
#include "ecs-core/manager/Component_manager.h"
#include "ecs-core/manager/Entity_handle.h"
#include <memory>

namespace ecs {
class World_public {
 public:
  using sys_ptr = std::unique_ptr<I_system>;
  template <typename T>
  using mgr_ptr = std::unique_ptr<T>;

 public:
  World_public();
  ~World_public();

  void add_system(sys_ptr s);

  template <typename T>
  void add_manager(std::unique_ptr<Component_manager<T>> m);
  template <typename T>
  void remove_manager();

  Entity_handle create_entity();

  void update(float dt);

 private:
  class Impl;
  std::unique_ptr<Impl> impl_;
};
}  // namespace ecs