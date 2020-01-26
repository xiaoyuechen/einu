#ifndef ENTITY_MANAGER_H_
#define ENTITY_MANAGER_H_

#include <atomic>
#include <map>
#include <memory>
#include <optional>
#include <vector>

#include "ecs-core/component_manager.h"
#include "ecs-core/component_mask.h"
#include "ecs-core/component_type_index.h"
#include "ecs-core/entity_id_manager.h"
#include "ecs-core/i_system.h"
#include "ecs-core/utility/type_list.h"

namespace ecs {

template <typename SystemPolicy, typename ComponentPolicy>
class World : SystemPolicy, ComponentPolicy {
 public:
  void Update(float dt) { SystemPolicy::Update(dt); }
};

template <typename ComponentType, std::size_t Count>
struct ComponentSetting {
  using Type = ComponentType;
  static constexpr std::size_t count = Count;
};

template <typename... ComponentSettings>
using ComponentSettingList = TypeList<ComponentSettings...>;

template <typename ComponentSettingList>
struct ComponentSettingListToTuple;

template <typename... ComponentSettings>
struct ComponentSettingListToTuple<ComponentSettingList<ComponentSettings...>> {
  using Tuple = std::tuple<typename ComponentSettings::Type...>;
};

template <typename ComponentSettingList>
class ComponentPolicy {
 public:
  template <typename ComponentType>
  ComponentManager<ComponentType>& GetComponentManager();

 private:
  typename ComponentSettingListToTuple<ComponentSettingList>::Tuple tuple_;
};

using MyComponentSettingList =
    ComponentSettingList<ComponentSetting<IComponent, 10>,
                         ComponentSetting<IComponent, 666>>;

class SystemA {};
class SystemB {};
class SystemC {};

class MySystemPolicy {
 public:
  //void Update(float dt) {
  //  system_a.Update(dt);
  //  ...
  //}

 private:
  SystemA system_a;
  SystemB system_b;
  SystemC system_c;
};

//////////////////////////////////////////////////////////////////////////

class EntityManager {
 public:
  EntityManager() = default;

  [[nodiscard]] EntityID SpawnEntity();

  template <typename T>
  const T& GetComponent(const EntityID& entity_id) const;
  template <typename T>
  T& GetComponent(const EntityID& entity_id);
  template <typename T>
  T& AddComponent(const EntityID& entity_id);
  template <typename T>
  void RemoveComponent(const EntityID& entity_id);

  void GetMatchingEntityIDs(std::vector<EntityID>* dest,
                            const ComponentMask& mask) const;
  void GetMatchingComponents(
      std::vector<std::map<ComponentTypeIndex, IComponent*>>* dest,
      const ComponentMask& mask);

  void AddSystem(std::unique_ptr<ISystem> system);

 private:
  template <typename T>
  const ComponentManager<T>& GetComponentManager() const;
  template <typename T>
  ComponentManager<T>& GetComponentManager();

 private:
  std::map<ComponentTypeIndex, IComponentManager> component_manager_map_;
  std::map<EntityID, ComponentMask> id_to_mask_map_;
  EntityIDManager entity_id_manager_;

  std::vector<std::unique_ptr<ISystem>> system_arr_;
  // std::map<ComponentMask, std::vector<EntityID>> entity_id_cache_;
};

//////////////////////////////////////////////////////////////////////////

template <typename T>
const T& EntityManager::GetComponent(const EntityID& entity_id) const {
  const auto& component_manager = GetComponentManager<T>();
  return component_manager.GetComponent(entity_id);
}

template <typename T>
T& EntityManager::GetComponent(const EntityID& entity_id) {
  return const_cast<T&>(
      static_cast<const EntityManager&>(*this).GetComponent<T>(entity_id));
}

template <typename T>
T& EntityManager::AddComponent(const EntityID& entity_id) {
  id_to_mask_map_[entity_id].Insert(GetComponentTypeIndex<T>());

  // for (auto&& pair : entity_id_cache_) {
  //  if (pair.first.HasType(GetComponentTypeIndex<T>()) &&
  //      (id_to_mask_map_[entity_id] & pair.first) == pair.first) {
  //    pair.second.push_back(entity_id);
  //  }
  //}

  auto& component_manager = GetComponentManager<T>();
  return component_manager.AddComponent(entity_id);
}  // namespace ecs

template <typename T>
void EntityManager::RemoveComponent(const EntityID& entity_id) {
  id_to_mask_map_[entity_id].Remove(GetComponentTypeIndex<T>());

  // for (auto&& pair : entity_id_cache_) {
  //  if (pair.first.HasType(GetComponentTypeIndex<T>())) {
  //    algo::erase_remove(
  //        pair.second, pair.second.begin(), pair.second.end(), entity_id);
  //  }
  //}

  auto& component_manager = GetComponentManager<T>();
  component_manager.RemoveComponent(entity_id);
}

template <typename T>
const ComponentManager<T>& EntityManager::GetComponentManager() const {
  return static_cast<const ComponentManager<T>&>(
      component_manager_map_.at(GetComponentTypeIndex<T>()));
}

template <typename T>
ComponentManager<T>& EntityManager::GetComponentManager() {
  return const_cast<ComponentManager<T>&>(
      static_cast<const EntityManager&>(*this).GetComponentManager<T>());
}

}  // namespace ecs

#endif  // ENTITY_MANAGER_H_
