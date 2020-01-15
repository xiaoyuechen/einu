#pragma once
#include <atomic>
#include <optional>
#include "ecs-core/manager/Entity_id_manager.h"
#include "ecs-core/admin/Component_admin.h"
#include "ecs-core/manager/Component_mask_manager.h"

namespace ecs {
class Entity_manager {
 public:
  class Handle;

 private:
  using entity_component_mask_map = std::map<Entity_id, Component_mask>;

 public:
  Entity_manager() = default;

  [[nodiscard]] Handle spawn_entity();

  template <typename T>
  std::optional<typename Component_manager<T>::Handle> get_component(
      const Entity_id& e);
  template <typename T>
  typename Component_manager<T>::Handle add_component(const Entity_id& e);
  template <typename T>
  void remove_component(const Entity_id& e);

  Component_admin& get_component_admin();
  Component_mask_manager& get_component_mask_manager();

 private:
  Entity_id_manager id_manager_;
  Component_admin comp_admin_;
  Component_mask_manager comp_mask_manager_;
};

class Entity_manager::Handle {
 public:
  Handle(const Entity_id& e, Entity_manager& m);

  Entity_id* operator->();
  const Entity_id* operator->() const;
  Entity_id& operator*();
  const Entity_id& operator*() const;

  template <typename T>
  typename Component_manager<T>::Handle add_component();

  template <typename T>
  void remove_component();

  template <typename T>
  std::optional<typename Component_manager<T>::Handle> get_component();

 private:
  Entity_id entity_;
  Entity_manager& manager_;
};
}  // namespace ecs

namespace ecs {
template <typename T>
inline std::optional<typename Component_manager<T>::Handle>
Entity_manager::get_component(const Entity_id& e) {
  auto m = comp_admin_.get_manager<T>();
  if (m.has_value()) {
    auto c = m.value()->get(e);
    if (c.has_value()) {
      return c.value();
    }
  }
  return std::nullopt;
}

template <typename T>
inline typename Component_manager<T>::Handle Entity_manager::add_component(
    const Entity_id& e) {
  assert(!get_component<T>(e).has_value() && "entity already has component");
  auto m = comp_admin_.get_manager<T>();
  assert(m.has_value() && "component manager not found in component admin");
  auto c = m.value()->add(e);
  comp_mask_manager_.add<T>(e);
  return c;
}

template <typename T>
inline void Entity_manager::remove_component(const Entity_id& e) {
  auto c = get_component<T>(e);
  assert(c.has_value() && "entity does not have component");
  c->destroy();
  comp_mask_manager_.remove<T>(e);
}

inline typename Entity_id* Entity_manager::Handle::operator->() {
  return &entity_;
}
inline typename const Entity_id* Entity_manager::Handle::operator->() const {
  return &entity_;
}
inline typename Entity_id& Entity_manager::Handle::operator*() { return entity_; }
inline typename const Entity_id& Entity_manager::Handle::operator*() const {
  return entity_;
}

template <typename T>
inline typename Component_manager<T>::Handle
Entity_manager::Handle::add_component() {
  return manager_.add_component<T>(entity_);
}

template <typename T>
inline void Entity_manager::Handle::remove_component() {
  manager_.remove_component<T>(entity_);
}

template <typename T>
inline std::optional<typename Component_manager<T>::Handle>
Entity_manager::Handle::get_component() {
  return manager_.get_component<T>(entity_);
}
}  // namespace ecs