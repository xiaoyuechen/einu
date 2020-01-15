#pragma once
#include <atomic>
#include <optional>
#include "ecs-core/component/Component_type.h"
#include "ecs-core/entity/Entity.h"
#include "ecs-core/manager/Component_manager.h"
#include "ecs-core/manager/Entity_id_manager.h"
#include "ecs-core/admin/Component_admin.h"

namespace ecs {
class Entity_manager {
 public:
  class Handle;

 private:
  using Component_manager_map =
      std::map<Component_type, std::unique_ptr<I_component_manager>>;

 public:
  Entity_manager(std::unique_ptr<Component_admin> comp_admin);

  [[nodiscard]] Handle spawn_entity();

  template <typename T>
  std::optional<typename Component_manager<T>::Handle> get_component(
      const Entity& e);

  template <typename T>
  typename Component_manager<T>::Handle add_component(const Entity& e);

  template <typename T>
  void remove_component(const Entity& e);

 private:
  Entity_id_manager id_manager_;
  std::unique_ptr<Component_admin> comp_admin_;
};

class Entity_manager::Handle {
 public:
  Handle(const Entity& e, Entity_manager& m);

  Entity* operator->();
  const Entity* operator->() const;
  Entity& operator*();
  const Entity& operator*() const;

  template <typename T>
  typename Component_manager<T>::Handle add_component();

  template <typename T>
  void remove_component();

  template <typename T>
  std::optional<typename Component_manager<T>::Handle> get_component();

 private:
  Entity entity_;
  Entity_manager& manager_;
};
}  // namespace ecs

namespace ecs {
template <typename T>
inline std::optional<typename Component_manager<T>::Handle>
Entity_manager::get_component(const Entity& e) {
  auto m = comp_admin_->get_manager<T>();
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
    const Entity& e) {
  assert(!get_component<T>(e).has_value() && "entity already has component");
  auto m = comp_admin_->get_manager<T>();
  assert(m.has_value() && "component manager not found in component admin");
  return m.value()->add(e);
}

template <typename T>
inline void Entity_manager::remove_component(const Entity& e) {
  auto c = get_component<T>(e);
  assert(c.has_value() && "enitity does not have component");
  c.value().destroy();
}

inline typename Entity* Entity_manager::Handle::operator->() {
  return &entity_;
}
inline typename const Entity* Entity_manager::Handle::operator->() const {
  return &entity_;
}
inline typename Entity& Entity_manager::Handle::operator*() { return entity_; }
inline typename const Entity& Entity_manager::Handle::operator*() const {
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