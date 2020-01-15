#pragma once
#include <map>
#include <mutex>
#include <memory>
#include <optional>
#include "ecs-core/entity/Entity_id.h"
#include "ecs-core/manager/I_component_manager.h"
#include "ecs-core/component/I_component.h"
#include "ecs-core/object-pool/Fixed_pool.h"

namespace ecs {
template <typename T>
class Component_manager : public I_component_manager {
  static_assert(std::is_base_of<I_component, T>() &&
                "T must inherit from Component class");
 public:
  class Handle;

 public:
  using Map = std::map<Entity_id, T*>;
  using Pool = Fixed_pool<T>;

 public:
  Component_manager(std::unique_ptr<Pool> pool);
  ~Component_manager() = default;

  Handle add(const Entity_id& entity);
  [[nodiscard]] std::optional<Handle> get(const Entity_id& entity);
  void remove(const Entity_id& entity);

 private:
  std::unique_ptr<Pool> pool_;
  Map map_;
  std::mutex mutex_;
};

template <typename T>
class Component_manager<T>::Handle {
 public:
  Handle(T& comp, const Entity_id& entity, Component_manager<T>& manager);
  T* operator->();
  const T* operator->() const;
  T& operator*();
  const T& operator*() const;
  const Entity_id& get_owner() const;
  void destroy();

 private:
  T& comp_;
  Entity_id entity_;
  Component_manager<T>& manager_;
};

template<typename T>
std::unique_ptr<Component_manager<T>> create_component_manager(
    size_t pool_size);
}  // namespace ecs

namespace ecs {
template <typename T>
inline Component_manager<T>::Component_manager(std::unique_ptr<Pool> pool)
    : pool_(std::move(pool)) {}

template <typename T>
inline typename Component_manager<T>::Handle Component_manager<T>::add(
    const Entity_id& entity) {
  assert(!get(entity).has_value() && "entity already have component");
  auto& comp = pool_->aquire();
  auto lock = std::scoped_lock(mutex_);
  map_[entity] = &comp;
  return Handle(comp, entity, *this);
}

template <typename T>
inline std::optional<typename Component_manager<T>::Handle>
Component_manager<T>::get(const Entity_id& entity) {
  if (map_.find(entity) != std::end(map_)) {
    return Handle(*map_[entity], entity, *this);
  }
  return std::nullopt;
}

template <typename T>
inline void Component_manager<T>::remove(const Entity_id& entity) {
  assert(get(entity).has_value() && "entity does not have component");
  auto handle = get(entity).value();
  pool_->recall(*handle);
  auto lock = std::scoped_lock(mutex_);
  map_.erase(entity);
}

template <typename T>
inline T* Component_manager<T>::Handle::operator->() {
  return &comp_;
}

template <typename T>
inline const T* Component_manager<T>::Handle::operator->() const {
  return &comp_;
}

template <typename T>
inline T& Component_manager<T>::Handle::operator*() {
  return comp_;
}

template <typename T>
inline const T& Component_manager<T>::Handle::operator*() const {
  return comp_;
}

template <typename T>
inline const Entity_id& Component_manager<T>::Handle::get_owner() const {
  return entity_;
}

template <typename T>
inline void Component_manager<T>::Handle::destroy() {
  manager_.remove(entity_);
}

template <typename T>
inline Component_manager<T>::Handle::Handle(T& comp,
                                            const Entity_id& entity,
                                            Component_manager<T>& manager)
    : comp_(comp)
    , entity_(entity)
    , manager_(manager) {}

template <typename T>
std::unique_ptr<Component_manager<T>> create_component_manager(
    size_t pool_size) {
  auto p = std::make_unique<typename Component_manager<T>::Pool>(pool_size);
  auto m = std::make_unique<Component_manager<T>>(std::move(p));
  return m;
}
}  // namespace ecs