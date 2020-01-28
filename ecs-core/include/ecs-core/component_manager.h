#ifndef COMPONENT_MANAGER_H_
#define COMPONENT_MANAGER_H_

#include <map>
#include <mutex>

#include "ecs-core/entity_id.h"
#include "ecs-core/i_component.h"
#include "ecs-core/object-pool/fixed_size_pool.h"

namespace ecs {

template <typename T>
class ComponentManager {
  static_assert(std::is_base_of<IComponent, T>() &&
                "T must inherit from Component");

 public:
  using Map = std::map<EntityID, T*>;
  using Pool = FixedSizePool<T>;

 public:
  ComponentManager(std::unique_ptr<Pool> pool);
  ~ComponentManager() = default;

  T& AddComponent(const EntityID& eid);
  [[nodiscard]] const T& GetComponent(const EntityID& eid) const;
  [[nodiscard]] T& GetComponent(const EntityID& eid);
  void RemoveComponent(const EntityID& eid);

 private:
  std::unique_ptr<Pool> pool_;
  Map map_;
  std::mutex mutex_;
};

//////////////////////////////////////////////////////////////////////////

template <typename T>
ComponentManager<T>::ComponentManager(std::unique_ptr<Pool> pool)
    : pool_(std::move(pool)) {}

template <typename T>
T& ComponentManager<T>::AddComponent(const EntityID& entity) {
  assert(map_.find(entity) == map_.end() && "entity already have component");
  auto& comp = pool_->Acquire();
  auto lock = std::scoped_lock(mutex_);
  map_[entity] = &comp;
  return comp;
}

template <typename T>
const T& ComponentManager<T>::GetComponent(const EntityID& entity) const {
  return *map_.at(entity);
}

template <typename T>
T& ComponentManager<T>::GetComponent(const EntityID& entity) {
  return const_cast<T&>(
      static_cast<const ComponentManager<T>&>(*this).GetComponent(entity));
}

template <typename T>
void ComponentManager<T>::RemoveComponent(const EntityID& entity) {
  auto& comp = GetComponent(entity);
  pool_->Recall(comp);
  auto lock = std::scoped_lock(mutex_);
  map_.erase(entity);
}

}  // namespace ecs

#endif  // COMPONENT_MANAGER_H_