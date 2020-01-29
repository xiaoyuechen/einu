#ifndef COMPONENT_MANAGER_H_
#define COMPONENT_MANAGER_H_

#include <map>
#include <mutex>

#include "ecs-core/entity_id.h"
#include "ecs-core/i_component.h"
#include "ecs-core/object-pool/fixed_size_pool.h"
#include "ecs-core/threading_model.h"

namespace ecs {

template <typename T,
          typename ThreadingModel,
          typename PoolPolicy = FixedSizePool<T, ThreadingModel>>
class ComponentManager : public ThreadingModel, public PoolPolicy {
  static_assert(std::is_base_of<IComponent, T>() &&
                "T must inherit from Component");

 public:
  template <typename... PoolArgs>
  ComponentManager(PoolArgs&&... pool_args);

  T& AddComponent(const EntityID& eid);
  [[nodiscard]] const T& GetComponent(const EntityID& eid) const;
  [[nodiscard]] T& GetComponent(const EntityID& eid);
  void RemoveComponent(const EntityID& eid);

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
  ThreadingModel::Lock lock(*this);
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
  ThreadingModel::Lock lock(*this);
  map_.erase(eid);
}

}  // namespace ecs

#endif  // COMPONENT_MANAGER_H_