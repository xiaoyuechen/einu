#pragma once

#include <map>

#include "ecs-engine/core/component.h"
#include "ecs-engine/core/entity_id.h"
#include "ecs-engine/utility/fixed_size_pool.h"

namespace ecs {

class IComponentManager {};

template <typename T, typename ThreadingModel,
          typename PoolPolicy = FixedSizePool<T, ThreadingModel>>
class ComponentManager : public ThreadingModel,
                         public PoolPolicy,
                         public IComponentManager {
  static_assert(std::is_base_of<IComponent, T>() &&
                "T must inherit from Component");

 public:
  template <typename... PoolArgs>
  ComponentManager(PoolArgs&&... pool_args);

  T& AddComponent(const EntityID& eid);
  [[nodiscard]] const T& GetComponent(const EntityID& eid) const;
  [[nodiscard]] T& GetComponent(const EntityID& eid);
  void RemoveComponent(const EntityID& eid);
  bool HasComponent(const EntityID& eid) const noexcept;

 private:
  using Map = std::map<EntityID, T&>;

  Map map_;
};

//////////////////////////////////////////////////////////////////////////

template <typename T, typename ThreadingModel, typename PoolPolicy>
template <typename... PoolArgs>
inline ComponentManager<T, ThreadingModel, PoolPolicy>::ComponentManager(
    PoolArgs&&... pool_args)
    : PoolPolicy(std::forward<PoolArgs>(pool_args)...) {}

template <typename T, typename ThreadingModel, typename PoolPolicy>
T& ComponentManager<T, ThreadingModel, PoolPolicy>::AddComponent(
    const EntityID& eid) {
  assert(map_.find(eid) == map_.end() && "eid already have component");
  auto& comp = PoolPolicy::Acquire();
  typename ThreadingModel::Lock lock(*this);
  map_.insert({eid, comp});
  return comp;
}

template <typename T, typename ThreadingModel, typename PoolPolicy>
const T& ComponentManager<T, ThreadingModel, PoolPolicy>::GetComponent(
    const EntityID& entity) const {
  return map_.at(entity);
}

template <typename T, typename ThreadingModel, typename PoolPolicy>
T& ComponentManager<T, ThreadingModel, PoolPolicy>::GetComponent(
    const EntityID& eid) {
  return const_cast<T&>(
      static_cast<const ComponentManager<T, ThreadingModel, PoolPolicy>&>(*this)
          .GetComponent(eid));
}

template <typename T, typename ThreadingModel, typename PoolPolicy>
void ComponentManager<T, ThreadingModel, PoolPolicy>::RemoveComponent(
    const EntityID& eid) {
  auto& comp = GetComponent(eid);
  PoolPolicy::Recall(comp);
  typename ThreadingModel::Lock lock(*this);
  map_.erase(eid);
}

template <typename T, typename ThreadingModel, typename PoolPolicy>
inline bool ComponentManager<T, ThreadingModel, PoolPolicy>::HasComponent(
    const EntityID& eid) const noexcept {
  return map_.find(eid) != map_.end();
}

}  // namespace ecs