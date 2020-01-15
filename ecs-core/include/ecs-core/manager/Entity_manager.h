#pragma once
#include <atomic>
#include <optional>
#include "ecs-core/component/Component_type.h"
#include "ecs-core/entity/Entity.h"
#include "ecs-core/manager/Component_manager.h"
#include "ecs-core/manager/Entity_id_manager.h"

namespace ecs {

class EntityManager {
 public:
  class Handle;

 private:
  using Component_manager_map =
      std::map<Component_type, std::unique_ptr<I_component_manager>>;

 public:
  template <typename T>
  void add_component_manager(
      std::unique_ptr<Component_manager<T>> m);

  [[nodiscard]] Handle spawn_entity();

  template <typename T>
  std::optional<typename Component_manager<T>::Handle> get_component(const Entity& e);

  template <typename T>
  typename Component_manager<T>::Handle add_component(const Entity& e);

  template<typename T>
  void remove_component(const Entity& e);

 private:
  Entity_id_manager id_manager_;
  Component_manager_map component_manager_map_;
};

class EntityManager::Handle {
 public:
  Handle(const Entity& e, EntityManager& m);

  Entity* operator->();
  const Entity* operator->() const;
  Entity& operator*();
  const Entity& operator*() const;

  template <typename T>
  typename Component_manager<T>::Handle add_component();

 private:
  Entity entity_;
  EntityManager& manager_;
};
}  // namespace ecs

namespace ecs {
template <typename T>
inline void EntityManager::add_component_manager(
    std::unique_ptr<Component_manager<T>> m) {
  auto comp_type = type_of<T>();

  assert(component_manager_map_.find(comp_type) ==
             std::end(component_manager_map_) &&
         "component manager already exists");

  component_manager_map_[comp_type] = std::move(m);
}

template <typename T>
inline std::optional<typename Component_manager<T>::Handle>
EntityManager::get_component(
    const Entity& e) {
  auto comp_type = type_of<T>();
  auto found = component_manager_map_.find(comp_type);
  if (found != std::end(component_manager_map_)) {
    auto& m =
      static_cast<Component_manager<T>&>(*component_manager_map_[comp_type]);
    auto c = m.get(e);
    if (c.has_value()) {
      return Component_manager<T>::Handle(*c.value(), e, m);
    }
  }
  return std::nullopt;
}

template <typename T>
inline typename Component_manager<T>::Handle EntityManager::add_component(
    const Entity& e) {
    assert(!get_component<T>(e).has_value() && "entity already has component");
  auto comp_type = type_of<T>();
  auto& m =
      static_cast<Component_manager<T>&>(*component_manager_map_[comp_type]);
  auto c = m.add(e);
  return Component_manager<T>::Handle(*c, e, m);
}

template <typename T>
inline void EntityManager::remove_component(const Entity& e) {}

inline typename Entity* EntityManager::Handle::operator->() { return &entity_; }
inline typename const Entity* EntityManager::Handle::operator->() const { return &entity_; }
inline typename Entity& EntityManager::Handle::operator*() { return entity_; }
inline typename const Entity& EntityManager::Handle::operator*() const { return entity_; }

template <typename T>
inline typename Component_manager<T>::Handle EntityManager::Handle::add_component() {
  return manager_.add_component<T>(entity_);
}
}  // namespace ecs