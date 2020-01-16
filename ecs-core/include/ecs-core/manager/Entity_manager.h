#pragma once
#include <atomic>
#include <optional>
#include "ecs-core/manager/Entity_id_manager.h"
#include "ecs-core/admin/Component_manager_admin.h"
#include "ecs-core/manager/Component_mask_manager.h"

namespace ecs {
class Entity_manager {
 private:
  using entity_component_mask_map = std::map<Entity_id, Component_mask>;

 public:
  Entity_manager() = default;

  [[nodiscard]] Entity_id spawn_entity();

  template <typename T>
  T& get_component(const Entity_id& e);
  template <typename T>
  T& add_component(const Entity_id& e);
  template <typename T>
  void remove_component(const Entity_id& e);

  Component_manager_admin& get_component_admin();
  Component_mask_manager& get_component_mask_manager();

 private:
  Entity_id_manager id_manager_;
  Component_manager_admin comp_admin_;
  Component_mask_manager comp_mask_manager_;
};

}  // namespace ecs

namespace ecs {
template <typename T>
inline T& Entity_manager::get_component(const Entity_id& e) {
  auto& m = comp_admin_.get_manager<T>();
  auto& c = m.get_component(e);
  return c;
}

template <typename T>
inline T& Entity_manager::add_component(const Entity_id& e) {
  auto& m = comp_admin_.get_manager<T>();
  auto& c = m.get_component(e);
  return c;
}

template <typename T>
inline void Entity_manager::remove_component(const Entity_id& e) {
  auto& m = comp_admin_.get_manager<T>();
  m.remove_component(e);
}
}  // namespace ecs