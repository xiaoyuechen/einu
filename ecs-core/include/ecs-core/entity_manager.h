#ifndef ENTITY_MANAGER_H_
#define ENTITY_MANAGER_H_

#include <map>
#include <tuple>

#include "ecs-core/component_cache_manager.h"
#include "ecs-core/component_manager.h"
#include "ecs-core/component_setting.h"
#include "ecs-core/entity.h"
#include "ecs-core/entity_id_manager.h"
#include "ecs-core/utility/type_list.h"
#include "ecs-core/utility/type_mapping.h"

namespace ecs {

namespace detail {
template <typename ComponentSetting, typename ThreadingModel>
struct TupleRefComponentManagerOf;
}  // namespace detail

template <typename ComponentSetting, typename ThreadingModel>
class ComponentManagerPolicy {
 public:
  template <typename T>
  using ComponentManager = ComponentManager<T, ThreadingModel>;

  template <typename... ComponentManagers>
  ComponentManagerPolicy(ComponentManagers&... comp_mgrs);

  template <typename T>
  const ComponentManager<T>& GetComponentManager(Type2Type<T>) const noexcept;
  template <typename T>
  ComponentManager<T>& GetComponentManager(Type2Type<T>) noexcept;

 private:
  using TupleRefComponentManager =
      typename detail::TupleRefComponentManagerOf<ComponentSetting,
                                                  ThreadingModel>::Type;

  TupleRefComponentManager t_ref_comp_mgr_;
};

namespace detail {
template <typename ThreadingModel, typename... Ts>
struct TupleRefComponentManagerOf<ComponentSetting<ComponentList<Ts...>>,
                                  ThreadingModel> {
  using Type = std::tuple<ComponentManager<Ts, ThreadingModel>&...>;
};
}  // namespace detail

template <typename ComponentSetting, typename ThreadingModel>
template <typename... ComponentManagers>
inline ComponentManagerPolicy<ComponentSetting, ThreadingModel>::
    ComponentManagerPolicy(ComponentManagers&... comp_mgrs)
    : t_ref_comp_mgr_(comp_mgrs...) {}

template <typename ComponentSetting, typename ThreadingModel>
template <typename T>
inline const typename ComponentManagerPolicy<
    ComponentSetting,
    ThreadingModel>::template ComponentManager<T>&
ComponentManagerPolicy<ComponentSetting, ThreadingModel>::GetComponentManager(
    Type2Type<T>) const noexcept {
  return std::get<ComponentManager<T>&>(t_ref_comp_mgr_);
}

template <typename ComponentSetting, typename ThreadingModel>
template <typename T>
inline typename ComponentManagerPolicy<
    ComponentSetting,
    ThreadingModel>::template ComponentManager<T>&
ComponentManagerPolicy<ComponentSetting, ThreadingModel>::GetComponentManager(
    Type2Type<T>) noexcept {
  return const_cast<ComponentManager<T>&>(
      static_cast<const ComponentManagerPolicy&>(*this)
          .GetComponentManager<T>());
}

template <typename ComponentSetting, typename ComponentManagerPolicy>
class EntityManager : public ComponentManagerPolicy {
 public:
  EntityID SpawnEntity();

  template <typename T>
  void AddComponent(const EntityID& eid);
  template <typename T>
  void RemoveComponent(const EntityID& eid);

  const Entity<ComponentSetting>& GetEntity(const EntityID& eid) const;
  Entity<ComponentSetting>& GetEntity(const EntityID& eid);

  template <typename... Ts>
  void GetMatchingComponents(std::vector<std::tuple<Ts&...>>& dest);

  template <typename... Ts>
  void RegisterInterest(Type2Type<ComponentList<Ts...>>);

 private:
  template <typename T>
  using ComponentManager =
      typename ComponentManagerPolicy::template ComponentManager<T>;

  template <typename T>
  const ComponentManager<T>& GetComponentManager() const;
  template <typename T>
  ComponentManager<T>& GetComponentManager();

  EntityIDManager ett_id_mgr_;
  std::map<EntityID, Entity<ComponentSetting>> ett_map_;
  ComponentCacheManager<ComponentSetting> comp_cache_mgr_;
};

//////////////////////////////////////////////////////////////////////////

template <typename ComponentSetting, typename ComponentManagerPolicy>
template <typename T>
inline void
EntityManager<ComponentSetting, ComponentManagerPolicy>::AddComponent(
    const EntityID& eid) {
  auto& mgr = GetComponentManager<T>();
  auto& comp = mgr.AddComponent(eid);
  auto& ett = ett_map_.at(eid);
  ett.AddComponent<T>(comp);

  comp_cache_mgr_.AddEntity(
      eid, ett.GetComponentMask(), ett.GetComponentArray());
}

template <typename ComponentSetting, typename ComponentManagerPolicy>
template <typename T>
inline void
EntityManager<ComponentSetting, ComponentManagerPolicy>::RemoveComponent(
    const EntityID& eid) {
  auto& ett = ett_map_.at(eid);

  comp_cache_mgr_.RemoveEntity(eid, ett.GetComponentMask());

  auto& mgr = GetComponentManager<T>();
  mgr.RemoveComponent(eid);
  ett.RemoveComponent<T>();
}

template <typename ComponentSetting, typename ComponentManagerPolicy>
template <typename... Ts>
inline void
EntityManager<ComponentSetting, ComponentManagerPolicy>::GetMatchingComponents(
    std::vector<std::tuple<Ts&...>>& dest) {
  auto comp_mask = ComponentSetting::template GetComponentMask<Ts...>();
  auto& comp_arrs = comp_cache_mgr_.GetComponentArrays(comp_mask);

  dest.clear();
  for (auto&& comp_arr : comp_arrs) {
    dest.emplace_back(comp_arr.Get<Ts>()...);
  }
}

template <typename ComponentSetting, typename ComponentManagerPolicy>
template <typename... Ts>
inline void
EntityManager<ComponentSetting, ComponentManagerPolicy>::RegisterInterest(
    Type2Type<ComponentList<Ts...>>) {
  const auto comp_mask = ComponentSetting::template GetComponentMask<Ts...>();
  comp_cache_mgr_.RegisterComponentMask(comp_mask);
}

template <typename ComponentSetting, typename ComponentManagerPolicy>
EntityID
EntityManager<ComponentSetting, ComponentManagerPolicy>::SpawnEntity() {
  auto eid = ett_id_mgr_.GenEntityID();
  ett_map_.insert({eid, Entity<ComponentSetting>()});
  return eid;
}

template <typename ComponentSetting, typename ComponentManagerPolicy>
inline const Entity<ComponentSetting>&
EntityManager<ComponentSetting, ComponentManagerPolicy>::GetEntity(
    const EntityID& eid) const {
  return ett_map_.at(eid);
}

template <typename ComponentSetting, typename ComponentManagerPolicy>
inline Entity<ComponentSetting>&
EntityManager<ComponentSetting, ComponentManagerPolicy>::GetEntity(
    const EntityID& eid) {
  return const_cast<Entity<ComponentSetting>&>(
      static_cast<const EntityManager&>(*this).GetEntity(eid));
}

template <typename ComponentSetting, typename ComponentManagerPolicy>
template <typename T>
inline const typename EntityManager<ComponentSetting, ComponentManagerPolicy>::
    template ComponentManager<T>&
    EntityManager<ComponentSetting,
                  ComponentManagerPolicy>::GetComponentManager() const {
  return ComponentManagerPolicy::GetComponentManager(Type2Type<T>{});
}

template <typename ComponentSetting, typename ComponentManagerPolicy>
template <typename T>
inline typename EntityManager<
    ComponentSetting,
    ComponentManagerPolicy>::template ComponentManager<T>&
EntityManager<ComponentSetting, ComponentManagerPolicy>::GetComponentManager() {
  return const_cast<ComponentManager<T>&>(
      static_cast<const EntityManager&>(*this).GetComponentManager<T>());
}

}  // namespace ecs

#endif  // ENTITY_MANAGER_H_
