#pragma once
#include "ecs-core/manager/Entity_manager.h"

namespace ecs {
template <typename T>
class Component_handle;

class Entity_handle {
 public:
  Entity_handle(const Entity_id& entity, Entity_manager& manager);

  Entity_id* operator->();
  const Entity_id* operator->() const;
  Entity_id& operator*();
  const Entity_id& operator*() const;

  template <typename T>
  Component_handle<T> add_component();
  template <typename T>
  void remove_component();
  template <typename T>
  Component_handle<T> get_component();

 private:
  Entity_id entity_;
  Entity_manager& manager_;
};

template <typename T>
class Component_handle {
 public:
  Component_handle(Entity_handle& entity_handle, T& component);

  T* operator->();
  const T* operator->() const;
  T& operator*();
  const T& operator*() const;

  Entity_handle& get_owner();
  const Entity_handle& get_owner() const;

 private:
  Entity_handle& entity_handle_;
  T& component_;
};

template <typename T>
inline Component_handle<T>::Component_handle(Entity_handle& entity_handle,
                                             T& component)
    : entity_handle_(entity_handle)
    , component_(component) {}

template <typename T>
inline T* Component_handle<T>::operator->() {
  return &component_;
}

template <typename T>
inline const T* Component_handle<T>::operator->() const {
  return &component_;
}

template <typename T>
inline T& Component_handle<T>::operator*() {
  return component_;
}

template <typename T>
inline const T& Component_handle<T>::operator*() const {
  return component_;
}

template <typename T>
inline Entity_handle& Component_handle<T>::get_owner() {
  return entity_handle_;
}

template <typename T>
inline const Entity_handle& Component_handle<T>::get_owner() const {
  return entity_handle_;
}


}  // namespace ecs

namespace ecs {
inline Entity_handle::Entity_handle(const Entity_id& entity,
                                    Entity_manager& manager)
    : entity_(entity)
    , manager_(manager) {}

inline Entity_id* Entity_handle::operator->() { return &entity_; }
inline const Entity_id* Entity_handle::operator->() const { return &entity_; }
inline Entity_id& Entity_handle::operator*() { return entity_; }
inline const Entity_id& Entity_handle::operator*() const { return entity_; }

template <typename T>
inline Component_handle<T> Entity_handle::add_component() {
  manager_.add_component<T>(entity_);
  return Component_handle<T>(*this);
}

template <typename T>
inline void Entity_handle::remove_component() {
  manager_.remove_component<T>(entity_);
}

template <typename T>
inline Component_handle<T> Entity_handle::get_component() {
  auto& c = manager_.get_component<T>(entity_);
  return Component_handle(c, entity_, manager_);
}
}  // namespace ecs