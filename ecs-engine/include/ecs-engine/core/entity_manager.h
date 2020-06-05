#pragma once

#include <map>
#include <tuple>

#include "ecs-engine/core/component_manager_set.h"
#include "ecs-engine/core/detail/component_mask.h"
#include "ecs-engine/core/detail/entity_cache_manager.h"
#include "ecs-engine/core/detail/entity_id_manager.h"
#include "ecs-engine/core/entity.h"
#include "ecs-engine/core/entity_handle.h"
#include "ecs-engine/core/entity_pool.h"
#include "ecs-engine/core/singleton_component_set.h"
#include "ecs-engine/extension/policy/threading_model.h"
#include "ecs-engine/utility/algorithm.h"
#include "ecs-engine/utility/tmp/type_mapping.h"

namespace ecs {

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
    auto eid = ett_id_mgr_.GenEntityID();
    typename ThreadingModel::Lock lock(*this);
    auto [it, success] = ett_map_.insert({eid, ett_pool_.Acquire()});
    if (success) {
      it->second.SetEntityID(eid);
    }
    return EntityHandle(eid, *this);
  }

  template <typename... Ts>
  void GetMatchingComponentsEids(std::vector<std::tuple<Ts&...>>* tuple_dest,
                                 std::vector<EntityID>* eid_dest) const {
    cache_mgr_.GetComponentsEids<Ts...>(tuple_dest, eid_dest);
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
    cache_mgr_.RegisterInterest<Ts...>();
  }

  std::size_t GetEntityCount() const noexcept { return ett_map_.size(); }

  template <typename T>
  T& AddComponent(const EntityID& eid) {
    auto& mgr = GetComponentManager<T>();
    typename ThreadingModel::Lock lock(*this);
    auto& comp = mgr.AddComponent(eid);
    auto& ett = ett_map_.at(eid);
    ett.AddComponent<T>(comp);
    cache_mgr_.RegisterEntity(ett);
    return comp;
  }

  template <typename T>
  void RemoveComponent(const EntityID& eid) {
    auto& ett = ett_map_.at(eid);
    typename ThreadingModel::Lock lock(*this);
    cache_mgr_.UnregisterEntity(ett);
    auto& mgr = GetComponentManager<T>();
    mgr.RemoveComponent(eid);
    ett.RemoveComponent<T>();

    if (ett.GetComponentCount() == 0) {
      RecallEntity(ett);
    }
  }

  template <typename T>
  const T& GetComponent(const EntityID& eid) const {
    auto& mgr = GetComponentManager<T>();
    return mgr.GetComponent(eid);
  }

  template <typename T>
  T& GetComponent(const EntityID& eid) {
    auto& mgr = GetComponentManager<T>();
    return mgr.GetComponent(eid);
  }

  template <typename T>
  bool HasComponent(const EntityID& eid) const {
    return GetComponentManager<T>().HasComponent(eid);
  }

  bool IsEntityIDValid(const EntityID& eid) const {
    return ett_map_.find(eid) != ett_map_.end();
  }

  const Entity& GetEntity(const EntityID& eid) const {
    return ett_map_.at(eid);
  }

  Entity& GetEntity(const EntityID& eid) { return ett_map_.at(eid); }

  void DestroyEntity(const EntityID& eid) {
    auto& ett = GetEntity(eid);
    typename ThreadingModel::Lock lock(*this);
    for (auto&& [idx, comp] : ett.GetComponentMap()) {
      component_managers_[idx].RemoveComponent(eid);
    }
    RecallEntity(ett);
  }

 private:
  using EntityCacheManager = detail::EntityCacheManager<ThreadingModel>;

  EntityID CreateEntityID() {
    auto eid = ett_id_mgr_.GenEntityID();
    typename ThreadingModel::Lock lock(*this);
    ett_map_.insert({eid, Entity(eid)});
    return eid;
  }

  void RecallEntity(const Entity& ett) {
    auto id = ett.GetEntityID();
    ett_pool_.Recall(ett);
    ett_map_.erase(eid);
  }

  template <typename T>
  const ComponentManager<T>& GetComponentManager() const {
    return component_managers_.Get<T>();
  }

  template <typename T>
  ComponentManager<T>& GetComponentManager() {
    return component_managers_.Get<T>();
  }

  detail::EntityIDManager ett_id_mgr_;
  std::map<EntityID, Entity&> ett_map_;
  EntityCacheManager cache_mgr_;
  ComponentManagerSet& component_managers_;
  SingletonComponentSet& singleton_components_;
  EntityPool& ett_pool_;
};

}  // namespace ecs