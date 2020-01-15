#pragma once
#include "ecs-core/manager/I_component_manager.h"
#include "ecs-core/component/I_component.h"
#include "ecs-core/entity/Entity_id.h"
#include "ecs-core/object-pool/Fixed_pool.h"
#include <map>
#include <mutex>
#include <memory>

namespace ecs {
template <typename T>
class Component_manager : public I_component_manager {
  static_assert(std::is_base_of<I_component, T>() &&
                "T must inherit from Component class");

 public:
  using Map = std::map<Entity_id, T*>;
  using Pool = Fixed_pool<T>;

 public:
  Component_manager(std::unique_ptr<Pool> pool);
  ~Component_manager() = default;

  T& add(const Entity_id& entity);
  [[nodiscard]] T& get(const Entity_id& entity);
  void remove(const Entity_id& entity);

 private:
  std::unique_ptr<Pool> pool_;
  Map map_;
  std::mutex mutex_;
};

template <typename T>
std::unique_ptr<Component_manager<T>> create_component_manager(
    size_t pool_size);
}  // namespace ecs

namespace ecs {
template <typename T>
inline Component_manager<T>::Component_manager(std::unique_ptr<Pool> pool)
    : pool_(std::move(pool)) {}

template <typename T>
inline T& Component_manager<T>::add(const Entity_id& entity) {
  assert(map_.find(entity) == map_.end() && "entity already have component");
  auto& comp = pool_->aquire();
  auto lock = std::scoped_lock(mutex_);
  map_[entity] = &comp;
  return comp;
}

template <typename T>
inline T& Component_manager<T>::get(
    const Entity_id& entity) {
  return *map_.at(entity);
}

template <typename T>
inline void Component_manager<T>::remove(const Entity_id& entity) {
  auto& comp = get(entity);
  pool_->recall(comp);
  auto lock = std::scoped_lock(mutex_);
  map_.erase(entity);
}

template <typename T>
std::unique_ptr<Component_manager<T>> create_component_manager(
    size_t pool_size) {
  auto p = std::make_unique<typename Component_manager<T>::Pool>(pool_size);
  auto m = std::make_unique<Component_manager<T>>(std::move(p));
  return m;
}
}  // namespace ecs