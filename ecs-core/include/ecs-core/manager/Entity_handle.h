#pragma once
#include "ecs-core/manager/Entity_manager.h"

namespace ecs {
class Entity_handle {
 public:
  Entity_handle(const Entity_id& e, Entity_manager& m);

  Entity_id* operator->();
  const Entity_id* operator->() const;
  Entity_id& operator*();
  const Entity_id& operator*() const;

  template <typename T>
  Entity_handle add_component();

  template <typename T>
  void remove_component();

  template <typename T>
  std::optional<Entity_handle> get_component();

 private:
  Entity_id entity_;
  Entity_manager& manager_;
};
}

