#pragma once

#include <map>
#include <utility>

#include "ecs-engine/core/entity_id.h"
#include "ecs-engine/core/i_component.h"
#include "ecs-engine/utility/fixed_size_pool.h"

namespace ecs {

class IComponentManager {
 public:
  virtual ~IComponentManager() = default;
  virtual void RemoveComponent(EntityID eid) = 0;
};

template <typename T, typename PoolPolicy = FixedSizePool<T>>
class ComponentManager : public PoolPolicy, public IComponentManager {
  static_assert(std::is_base_of<IComponent, T>() &&
                "T must inherit from IComponent");

 public:
  template <typename... PoolArgs>
  ComponentManager(PoolArgs&&... pool_args)
      : PoolPolicy(std::forward<PoolArgs>(pool_args)...) {}

  T& AddComponent(EntityID eid) {
    auto& comp = PoolPolicy::Acquire();
    map_.insert({eid, comp});
    return comp;
  }

  [[nodiscard]] const T& GetComponent(EntityID eid) const {
    return map_.at(eid);
  }

  [[nodiscard]] T& GetComponent(EntityID eid) {
    return const_cast<T&>(
        static_cast<const ComponentManager&>(*this).GetComponent(eid));
  }

  virtual void RemoveComponent(EntityID eid) override {
    auto& comp = GetComponent(eid);
    PoolPolicy::Recall(comp);
    map_.erase(eid);
  }

  bool HasComponent(EntityID eid) const noexcept {
    return map_.find(eid) != map_.end();
  }

 private:
  using Map = std::map<EntityID, T&>;
  Map map_;
};

}  // namespace ecs