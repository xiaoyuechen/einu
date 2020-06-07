#pragma once

#include <map>
#include <tuple>

#include "ecs-engine/core/component_entity_buffer.h"
#include "ecs-engine/core/component_manager_set.h"
#include "ecs-engine/core/detail/component_mask.h"
#include "ecs-engine/core/detail/entity_cache_manager.h"
#include "ecs-engine/core/detail/entity_id_manager.h"
#include "ecs-engine/core/entity_data.h"
#include "ecs-engine/core/entity_handle.h"
#include "ecs-engine/core/entity_pool.h"
#include "ecs-engine/core/singleton_component_set.h"
#include "ecs-engine/extension/policy/threading_model.h"
#include "ecs-engine/utility/algorithm.h"
#include "ecs-engine/utility/tmp/type_mapping.h"

namespace ecs {

namespace detail {
template <typename Tuple, typename Iter, size_t... Is>
auto MakeComponentTuple(Iter iter, std::index_sequence<Is...>) {
  return std::forward_as_tuple(
      static_cast<typename std::tuple_element<Is, Tuple>::type>(
          **(iter + Is))...);
}
}  // namespace detail

template <typename ComponentManagerSet = ComponentManagerSet,
          typename SingletonComponentSet = SingletonComponentSet,
          typename EntityPool = EntityPool,
          typename ThreadingModel = MultiThreaded>
class EntityManager : public ThreadingModel {
 public:
  using EntityHandle = EntityHandle<EntityManager>;
  template <typename T>
  using ComponentManager =
      typename ComponentManagerSet::template ComponentManager<T>;

  EntityManager(ComponentManagerSet& component_manager_set,
                SingletonComponentSet& singleton_component_set,
                EntityPool& ett_pool)
      : component_managers_(component_manager_set)
      , singleton_components_(singleton_component_set)
      , ett_pool_(ett_pool) {}

  EntityHandle CreateEntity() {
    typename ThreadingModel::Lock lock(*this);
    auto& ett = ett_pool_.Acquire();
    ett.SetEntityID(ett_id_mgr_.GenEntityID());
    ett.Activate();
    return EntityHandle(ett, *this);
  }

  template <typename... Ts>
  void GetMatchingComponentsEntities(ComponentEntityBuffer<Ts...>& dest) const {
    const auto& mask = detail::GetComponentMaskStatic<Ts...>();
    const auto& cache_data = cache_mgr_.GetCacheData(mask);
    const auto& comps = cache_data.comps;
    for (auto it = comps.begin(); it != comps.end(); it += sizeof...(Ts)) {
      auto tup = detail::MakeComponentTuple<std::tuple<Ts&...>>(
          it, std::make_index_sequence<sizeof...(Ts)>());
      dest.GetComponents().emplace_back(tup);
    }
    auto& etts = cache_data.etts;
    std::transform(etts.begin(), etts.end(),
                   std::back_inserter(dest.GetEntities()),
                   [](auto ett) { return std::ref(*ett); });
  }

  template <typename T>
  const T& GetSingletonComponent() const {
    return singleton_components_.Get<T>();
  }
  template <typename T>
  T& GetSingletonComponent() {
    return singleton_components_.Get<T>();
  }

  template <typename... Ts>
  void RegisterInterest() {
    cache_mgr_.RegisterInterest(&detail::GetComponentMaskStatic<Ts...>(),
                                {rtti::GetClassIndex<Ts>()...});
  }

  template <typename T>
  T& AddComponent(EntityData& ett) {
    return static_cast<T&>(AddComponent(ett, rtti::GetClassIndex<T>()));
  }

  template <typename T>
  void RemoveComponent(EntityData& ett) {
    RemoveComponent(ett, rtti::GetClassIndex<T>());
  }

  void DestroyEntity(EntityData& ett) {
    const auto& mask = ett.GetComponentMask();
    for (std::size_t i = 0; i != mask.size(); ++i) {
      if (mask[i]) {
        RemoveComponent(ett, rtti::ClassIndex(i));
      }
    }
  }

 private:
  using EntityCacheManager = detail::EntityCacheManager<ThreadingModel>;

  IComponent& AddComponent(EntityData& ett, rtti::ClassIndex idx) {
    typename ThreadingModel::Lock lock(*this);
    auto& mgr = component_managers_[idx];
    auto& comp = mgr.AddComponent(ett.GetEntityID());
    ett.AddComponent(idx, comp);
    cache_mgr_.AfterAddComponent(ett);
    return comp;
  }

  void RemoveComponent(EntityData& ett, rtti::ClassIndex idx) {
    typename ThreadingModel::Lock lock(*this);
    cache_mgr_.BeforeRemoveComponent(ett);
    auto& mgr = component_managers_[idx];
    mgr.RemoveComponent(ett.GetEntityID());
    ett.RemoveComponent(idx);

    if (ett.GetComponentCount() == 0) {
      ett_pool_.Recall(ett);
    }
  }

  detail::EntityIDManager ett_id_mgr_;
  EntityCacheManager cache_mgr_;
  ComponentManagerSet& component_managers_;
  SingletonComponentSet& singleton_components_;
  EntityPool& ett_pool_;
};

}  // namespace ecs