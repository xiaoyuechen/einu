#pragma once
#include "ecs-core/entities/Entity.h"
#include "ecs-core/object-pool/Fixed_pool.h"
#include <map>

namespace ecs {
template <typename T>
class Component_manager {
 public:
  class Handle;

 public:
  using Map = std::map<Entity, T*>;
  using Pool = Fixed_pool<T>;

 public:
  Component_manager(Pool& pool);
  void add(const Entity& entity);
  [[nodiscard]] Handle get(const Entity& entity);
  void remove(const Entity& entity);

 private:
  Pool& pool_;
  Map map_;
};

template <typename T>
class Component_manager<T>::Handle {
 public:
  Handle(T& comp, const Entity& entity, Component_manager<T>& manager);
  T* operator->();
  const T* operator->() const;
  void destroy();

 private:
  T& comp_;
  const Entity& entity_;
  Component_manager<T>& manager_;
};
}  // namespace ecs

namespace ecs {
template <typename T>
inline T* Component_manager<T>::Handle::operator->() {
  return &comp_;
}

template <typename T>
inline const T* Component_manager<T>::Handle::operator->() const {
  return &comp_;
}

template <typename T>
inline void Component_manager<T>::Handle::destroy() {
  manager_.remove(entity_);
}

template <typename T>
inline Component_manager<T>::Handle::Handle(T& comp,
                                            const Entity& entity,
                                            Component_manager<T>& manager)
    : comp_(comp)
    , entity_(entity)
    , manager_(manager) {}

template <typename T>
inline Component_manager<T>::Component_manager(Pool& pool)
    : pool_(pool) {}

template <typename T>
inline void Component_manager<T>::add(const Entity& entity) {
  map_[entity] = pool_.aquire();
}

template <typename T>
inline typename Component_manager<T>::Handle Component_manager<T>::get(
    const Entity& entity) {
  assert(map_.find(entity) != std::end(map_) &&
         "entity does not have component");
  return Handle(*map_[entity], entity, *this);
}

template <typename T>
inline void Component_manager<T>::remove(const Entity& entity) {
  auto found = map_.find(entity);
  assert(found != std::end(map_) && "entity does not have component");
  pool_.recall(found->second);
  map_.erase(found);
}
}  // namespace ecs