#ifndef ENTITY_MANAGER_H_
#define ENTITY_MANAGER_H_

#include <map>

#include "ecs-core/component_manager.h"
#include "ecs-core/component_setting.h"
#include "ecs-core/entity.h"
#include "ecs-core/entity_id_manager.h"
#include "ecs-core/utility/type_list.h"
#include "ecs-core/utility/type_mapping.h"
#include "ecs-core/component_cache_manager.h"

namespace ecs {


template <typename ComponentSetting, typename ComponentManagerPolicy>
class EntityManager : public ComponentManagerPolicy {
 public:
  template <typename T>
  const ComponentManager<T>& GetComponentManager() const;

  template <typename T>
  ComponentManager<T>& GetComponentManager();

  EntityID SpawnEntity() {
    auto eid = ett_id_mgr_.GenEntityID();
    ett_map_.insert({eid, Entity<ComponentSetting>()});
    return eid;
  }

  template <typename T>
  void AddComponent(const EntityID& eid) {
    auto& mgr = GetComponentManager<T>();
    auto& comp = mgr.AddComponent(eid);
    auto& ett = ett_map_.at(eid);
    ett.AddComponent<T>(comp);

    comp_cache_mgr_.AddEntity(
        eid, ett.GetComponentMask(), ett.GetComponentArray());
  }

  template <typename T>
  void RemoveComponent(const EntityID& eid) {
    auto& ett = ett_map_.at(eid);

    comp_cache_mgr_.RemoveEntity(eid, ett.GetComponentMask());

    auto& mgr = GetComponentManager<T>();
    mgr.RemoveComponent(eid);
    ett.RemoveComponent<T>();
  }

  const Entity<ComponentSetting>& GetEntity(const EntityID& eid) const {
    return ett_map_.at(eid);
  }

  Entity<ComponentSetting>& GetEntity(const EntityID& eid) {
    return const_cast<Entity<ComponentSetting>&>(
        static_cast<const EntityManager&>(*this).GetEntity(eid));
  }

  template <typename... Ts>
  void GetMatchingComponents(std::vector<std::tuple<Ts&...>>& dest) {
    auto comp_mask = ComponentSetting::template GetComponentMask<Ts...>();
    auto& comp_arrs = comp_cache_mgr_.GetComponentArrays(comp_mask);

    dest.clear();
    for (auto&& comp_arr : comp_arrs) {
      dest.emplace_back(comp_arr.Get<Ts>()...);
    }
  }

  template <typename... Ts>
  void RegisterInterest() {
    const auto comp_mask = ComponentSetting::template GetComponentMask<Ts...>();
    comp_cache_mgr_.RegisterComponentMask(comp_mask);
  }

 private:
  EntityIDManager ett_id_mgr_;
  std::map<EntityID, Entity<ComponentSetting>> ett_map_;
  ComponentCacheManager<ComponentSetting> comp_cache_mgr_;
};

//////////////////////////////////////////////////////////////////////////

template <typename ComponentSetting, typename ComponentManagerPolicy>
template <typename T>
inline const ComponentManager<T>&
EntityManager<ComponentSetting, ComponentManagerPolicy>::GetComponentManager()
    const {
  return ComponentManagerPolicy::GetComponentManager(Type2Type<T>{});
}

template <typename ComponentSetting, typename ComponentManagerPolicy>
template <typename T>
inline ComponentManager<T>&
EntityManager<ComponentSetting, ComponentManagerPolicy>::GetComponentManager() {
  return ComponentManagerPolicy::GetComponentManager(Type2Type<T>{});
}



}  // namespace ecs

#endif  // ENTITY_MANAGER_H_
