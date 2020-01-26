#include "ecs-core/entity_manager.h"

namespace ecs {

EntityID EntityManager::SpawnEntity() {
  return entity_id_manager_.GenEntityID();
}

void EntityManager::GetMatchingEntityIDs(std::vector<EntityID>* dest,
                                         const ComponentMask& mask) const {
  for (auto it = id_to_mask_map_.cbegin(); it != id_to_mask_map_.cend(); ++it) {
    if ((it->second & mask) == mask) {
      dest->push_back(it->first);
    }
  }
}

//void EntityManager::GetMatchingComponents(
//    std::vector<std::map<ComponentTypeIndex, IComponent*>>* dest,
//    const ComponentMask& mask) {}

void EntityManager::AddSystem(std::unique_ptr<ISystem> system) {
  //entity_id_cache_.insert(
  //    {system->GetComponentMask(), std::vector<EntityID>{}});
  system_arr_.push_back(std::move(system));
}

}  // namespace ecs