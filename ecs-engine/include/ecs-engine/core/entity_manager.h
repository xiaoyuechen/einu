#ifndef ENTITY_MANAGER_IMPL_H_
#define ENTITY_MANAGER_IMPL_H_

#include <map>
#include <tuple>

#include "ecs-engine/core/component_cache_manager.h"
#include "ecs-engine/core/component_setting.h"
#include "ecs-engine/core/entity.h"
#include "ecs-engine/core/entity_id_manager.h"
#include "ecs-engine/utility/algorithm.h"
#include "ecs-engine/utility/type_list.h"
#include "ecs-engine/utility/type_mapping.h"

namespace ecs {

template <typename ComponentSetting, typename ComponentManagerPolicy,
          typename ThreadingModel>
class EntityManager : public ComponentManagerPolicy, public ThreadingModel {
 public:
  using Entity = Entity<ComponentSetting>;

  class EntityHandle {
   public:
    EntityHandle(const EntityID& eid, EntityManager& ett_mgr);

    template <typename T>
    T& AddComponent();
    template <typename T>
    void RemoveComponent();
    template <typename T>
    const T& GetComponent() const;
    template <typename T>
    T& GetComponent();

    const EntityID& GetEntityID() const;

    void Destory();

   private:
    EntityID eid_;
    EntityManager& ett_mgr_;
  };

  template <typename... ComponentManagerPolicyArgs>
  EntityManager(ComponentManagerPolicyArgs&&... comp_mgr_args);

  EntityHandle CreateEntity();

  template <typename... Ts>
  void GetMatchingComponents(std::vector<std::tuple<Ts&...>>* tuple_dest,
                             std::vector<EntityID>* eid_dest);

  template <typename T>
  const T& GetSingletonComponent() const;
  template <typename T>
  T& GetSingletonComponent();

  template <typename... Ts>
  void RegisterInterest(Type2Type<ComponentList<Ts...>>);

  std::size_t GetEntityCount() const noexcept;

 private:
  template <typename T>
  using ComponentManager =
      typename ComponentManagerPolicy::template ComponentManager<T>;

  EntityID CreateEntityID();

  template <typename T>
  T& AddComponent(const EntityID& eid);
  template <typename T>
  void RemoveComponent(const EntityID& eid);
  template <typename T>
  const T& GetComponent(const EntityID& eid) const;
  template <typename T>
  T& GetComponent(const EntityID& eid);

  const Entity& GetEntity(const EntityID& eid) const;
  Entity& GetEntity(const EntityID& eid);

  void DestroyEntity(const EntityID& eid);

  template <typename T>
  const ComponentManager<T>& GetComponentManager() const;
  template <typename T>
  ComponentManager<T>& GetComponentManager();

  EntityIDManager ett_id_mgr_;
  std::map<EntityID, Entity> ett_map_;
  ComponentCacheManager<ComponentSetting, ThreadingModel> comp_cache_mgr_;
};

//////////////////////////////////////////////////////////////////////////

template <typename ComponentSetting, typename ComponentManagerPolicy,
          typename ThreadingModel>
inline EntityManager<ComponentSetting, ComponentManagerPolicy, ThreadingModel>::
    EntityHandle::EntityHandle(const EntityID& eid, EntityManager& ett_mgr)
    : eid_{eid}
    , ett_mgr_{ett_mgr} {}

template <typename ComponentSetting, typename ComponentManagerPolicy,
          typename ThreadingModel>
inline const EntityID&
EntityManager<ComponentSetting, ComponentManagerPolicy,
              ThreadingModel>::EntityHandle::GetEntityID() const {
  return eid_;
}

template <typename ComponentSetting, typename ComponentManagerPolicy,
          typename ThreadingModel>
inline void EntityManager<ComponentSetting, ComponentManagerPolicy,
                          ThreadingModel>::EntityHandle::Destory() {
  ett_mgr_.DestroyEntity(eid_);
}

template <typename ComponentSetting, typename ComponentManagerPolicy,
          typename ThreadingModel>
template <typename T>
inline T& EntityManager<ComponentSetting, ComponentManagerPolicy,
                        ThreadingModel>::EntityHandle::AddComponent() {
  return ett_mgr_.AddComponent<T>(eid_);
}

template <typename ComponentSetting, typename ComponentManagerPolicy,
          typename ThreadingModel>
template <typename T>
inline void EntityManager<ComponentSetting, ComponentManagerPolicy,
                          ThreadingModel>::EntityHandle::RemoveComponent() {
  ett_mgr_.RemoveComponent<T>(eid_);
}

template <typename ComponentSetting, typename ComponentManagerPolicy,
          typename ThreadingModel>
template <typename T>
inline const T& EntityManager<ComponentSetting, ComponentManagerPolicy,
                              ThreadingModel>::EntityHandle::GetComponent()
    const {
  return ett_mgr_.GetComponent<T>(eid_);
}

template <typename ComponentSetting, typename ComponentManagerPolicy,
          typename ThreadingModel>
template <typename T>
inline T& EntityManager<ComponentSetting, ComponentManagerPolicy,
                        ThreadingModel>::EntityHandle::GetComponent() {
  return ett_mgr_.GetComponent<T>(eid_);
}

template <typename ComponentSetting, typename ComponentManagerPolicy,
          typename ThreadingModel>
inline typename EntityManager<ComponentSetting, ComponentManagerPolicy,
                              ThreadingModel>::EntityHandle
EntityManager<ComponentSetting, ComponentManagerPolicy,
              ThreadingModel>::CreateEntity() {
  return EntityHandle(CreateEntityID(), *this);
}

template <typename ComponentSetting, typename ComponentManagerPolicy,
          typename ThreadingModel>
template <typename T>
inline T& EntityManager<ComponentSetting, ComponentManagerPolicy,
                        ThreadingModel>::AddComponent(const EntityID& eid) {
  auto& mgr = GetComponentManager<T>();
  auto& comp = mgr.AddComponent(eid);
  auto& ett = ett_map_.at(eid);
  typename ThreadingModel::Lock lock(*this);
  ett.AddComponent<T>(comp);

  comp_cache_mgr_.AddEntity(eid, ett.GetComponentMask(),
                            ett.GetComponentArray());

  return comp;
}

template <typename ComponentSetting, typename ComponentManagerPolicy,
          typename ThreadingModel>
template <typename T>
inline void
EntityManager<ComponentSetting, ComponentManagerPolicy,
              ThreadingModel>::RemoveComponent(const EntityID& eid) {
  auto& ett = ett_map_.at(eid);

  comp_cache_mgr_.RemoveEntity(eid, ett.GetComponentMask());

  auto& mgr = GetComponentManager<T>();
  mgr.RemoveComponent(eid);
  typename ThreadingModel::Lock lock(*this);
  ett.RemoveComponent<T>();
}

template <typename ComponentSetting, typename ComponentManagerPolicy,
          typename ThreadingModel>
template <typename T>
inline const T& EntityManager<ComponentSetting, ComponentManagerPolicy,
                              ThreadingModel>::GetComponent(const EntityID& eid)
    const {
  const auto& comp_mgr = GetComponentManager<T>();
  return comp_mgr.GetComponent(eid);
}

template <typename ComponentSetting, typename ComponentManagerPolicy,
          typename ThreadingModel>
template <typename T>
inline T& EntityManager<ComponentSetting, ComponentManagerPolicy,
                        ThreadingModel>::GetComponent(const EntityID& eid) {
  return const_cast<T&>(
      static_cast<const EntityManager&>(*this).GetComponent<T>(eid));
}

template <typename ComponentSetting, typename ComponentManagerPolicy,
          typename ThreadingModel>
template <typename... ComponentManagerPolicyArgs>
inline EntityManager<ComponentSetting, ComponentManagerPolicy, ThreadingModel>::
    EntityManager(ComponentManagerPolicyArgs&&... comp_mgr_args)
    : ComponentManagerPolicy(
          std::forward<ComponentManagerPolicyArgs>(comp_mgr_args)...) {}

template <typename ComponentSetting, typename ComponentManagerPolicy,
          typename ThreadingModel>
template <typename... Ts>
inline void
EntityManager<ComponentSetting, ComponentManagerPolicy, ThreadingModel>::
    GetMatchingComponents(std::vector<std::tuple<Ts&...>>* tuple_dest,
                          std::vector<EntityID>* eid_dest) {
  auto comp_mask = ComponentSetting::template GetComponentMask<Ts...>();
  auto& cache_data = comp_cache_mgr_.GetCacheData(comp_mask);

  tuple_dest->clear();
  for (auto&& comp_arr : cache_data.comp_arrs) {
    tuple_dest->emplace_back(comp_arr.Get<Ts>()...);
  }
  *eid_dest = cache_data.eid_arr;
}

template <typename ComponentSetting, typename ComponentManagerPolicy,
          typename ThreadingModel>
template <typename T>
inline const T& EntityManager<ComponentSetting, ComponentManagerPolicy,
                              ThreadingModel>::GetSingletonComponent() const {
  return ComponentManagerPolicy::template GetSingletonComponent<T>();
}

template <typename ComponentSetting, typename ComponentManagerPolicy,
          typename ThreadingModel>
template <typename T>
inline T& EntityManager<ComponentSetting, ComponentManagerPolicy,
                        ThreadingModel>::GetSingletonComponent() {
  return const_cast<T&>(
      static_cast<const EntityManager&>(*this).GetSingletonComponent<T>());
}

template <typename ComponentSetting, typename ComponentManagerPolicy,
          typename ThreadingModel>
template <typename... Ts>
inline void EntityManager<
    ComponentSetting, ComponentManagerPolicy,
    ThreadingModel>::RegisterInterest(Type2Type<ComponentList<Ts...>>) {
  const auto comp_mask = ComponentSetting::template GetComponentMask<Ts...>();
  comp_cache_mgr_.RegisterComponentMask(comp_mask);
}

template <typename ComponentSetting, typename ComponentManagerPolicy,
          typename ThreadingModel>
inline std::size_t EntityManager<ComponentSetting, ComponentManagerPolicy,
                                 ThreadingModel>::GetEntityCount() const
    noexcept {
  return ett_map_.size();
}

template <typename ComponentSetting, typename ComponentManagerPolicy,
          typename ThreadingModel>
inline EntityID EntityManager<ComponentSetting, ComponentManagerPolicy,
                              ThreadingModel>::CreateEntityID() {
  auto eid = ett_id_mgr_.GenEntityID();
  typename ThreadingModel::Lock lock(*this);
  ett_map_.insert({eid, Entity{}});
  return eid;
}

template <typename ComponentSetting, typename ComponentManagerPolicy,
          typename ThreadingModel>
inline const typename EntityManager<ComponentSetting, ComponentManagerPolicy,
                                    ThreadingModel>::Entity&
EntityManager<ComponentSetting, ComponentManagerPolicy,
              ThreadingModel>::GetEntity(const EntityID& eid) const {
  return ett_map_.at(eid);
}

template <typename ComponentSetting, typename ComponentManagerPolicy,
          typename ThreadingModel>
inline typename EntityManager<ComponentSetting, ComponentManagerPolicy,
                              ThreadingModel>::Entity&
EntityManager<ComponentSetting, ComponentManagerPolicy,
              ThreadingModel>::GetEntity(const EntityID& eid) {
  return const_cast<Entity&>(
      static_cast<const EntityManager&>(*this).GetEntity(eid));
}

template <typename ComponentSetting, typename ComponentManagerPolicy,
          typename ThreadingModel>
inline void EntityManager<ComponentSetting, ComponentManagerPolicy,
                          ThreadingModel>::DestroyEntity(const EntityID& eid) {
  auto& ett = GetEntity(eid);
  const auto& comp_mask = ett.GetComponentMask();
  auto check_remove_comp = [&](auto i) {
    if (comp_mask[i]) {
      RemoveComponent<ComponentSetting::ComponentTypeAt<i>>(eid);
    }
  };
  algo::StaticFor<ComponentSetting::GetComponentTypeCount()>(check_remove_comp);
  ett_map_.erase(eid);
}

template <typename ComponentSetting, typename ComponentManagerPolicy,
          typename ThreadingModel>
template <typename T>
inline const typename EntityManager<
    ComponentSetting, ComponentManagerPolicy,
    ThreadingModel>::template ComponentManager<T>&
EntityManager<ComponentSetting, ComponentManagerPolicy,
              ThreadingModel>::GetComponentManager() const {
  return ComponentManagerPolicy::GetComponentManager(Type2Type<T>{});
}

template <typename ComponentSetting, typename ComponentManagerPolicy,
          typename ThreadingModel>
template <typename T>
inline typename EntityManager<ComponentSetting, ComponentManagerPolicy,
                              ThreadingModel>::template ComponentManager<T>&
EntityManager<ComponentSetting, ComponentManagerPolicy,
              ThreadingModel>::GetComponentManager() {
  return const_cast<ComponentManager<T>&>(
      static_cast<const EntityManager&>(*this).GetComponentManager<T>());
}

}  // namespace ecs

#endif  // ENTITY_MANAGER_IMPL_H_
