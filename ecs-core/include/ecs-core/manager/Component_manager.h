#pragma once
#include "ecs-core/manager/I_component_manager.h"
#include "ecs-core/public-interface/Component.h"
#include "ecs-core/object-pool/Fixed_pool.h"
#include <map>
#include <mutex>

namespace ecs {
template <typename T>
class Component_manager : public I_component_manager {
  static_assert(std::is_base_of<Component, T>() &&
                "T must inherit from Component class");

 public:
  using Map = std::map<Entity_id, T*>;
  using Pool = Fixed_pool<T>;

 public:
  Component_manager(std::unique_ptr<Pool> pool);
  ~Component_manager() = default;

  T& add_component(const Entity_id& entity);
  [[nodiscard]] T& get_component(const Entity_id& entity);
  virtual void remove_component(const Entity_id& entity) override;

 private:
  std::unique_ptr<Pool> pool_;
  Map map_;
  std::mutex mutex_;
};
}  // namespace ecs

namespace ecs {
template <typename T>
inline Component_manager<T>::Component_manager(std::unique_ptr<Pool> pool)
    : pool_(std::move(pool)) {}

template <typename T>
inline T& Component_manager<T>::add_component(const Entity_id& entity) {
  assert(map_.find(entity) == map_.end() && "entity already have component");
  auto& comp = pool_->aquire();
  auto lock = std::scoped_lock(mutex_);
  map_[entity] = &comp;
  return comp;
}

template <typename T>
inline T& Component_manager<T>::get_component(
    const Entity_id& entity) {
  return *map_.at(entity);
}

template <typename T>
inline void Component_manager<T>::remove_component(const Entity_id& entity) {
  auto& comp = get_component(entity);
  pool_->recall(comp);
  auto lock = std::scoped_lock(mutex_);
  map_.erase(entity);
}
}  // namespace ecs