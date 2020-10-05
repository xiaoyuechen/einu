#pragma once

#include <algorithm>
#include <vector>

#include "einu-engine/core/component_entity_buffer.h"
#include "einu-engine/core/component_mask_storage.h"
#include "einu-engine/core/component_pool_manager.h"
#include "einu-engine/core/entity.h"
#include "einu-engine/core/entity_pool.h"
#include "einu-engine/core/singleton_component_manager.h"
#include "einu-engine/extension/policy/threading_model.h"

namespace einu {

class IEntityManager {};

template <typename ThreadingModel = MultiThreaded>
class EntityManager : public ThreadingModel, public IEntityManager {
 public:
  using size_type = std::size_t;

  EntityManager(IEntityPool& entity_pool,
                ComponentPoolManager& component_pool_manager,
                SingletonComponentManager& singleton_component_manager)
      : entity_pool_(entity_pool)
      , component_pool_manager_(component_pool_manager)
      , singleton_component_manager_(singleton_component_manager) {}

  IEntity& CreateEntity() {
    typename ThreadingModel::Lock lock(*this);
    auto& ett = entity_pool_.Acquire(*this);
    entities_.push_back(ett);
    return ett;
  }

  void AddEntity(IEntity& ett) {
    typename ThreadingModel::Lock lock(*this);
    entities_.push_back(ett);
  }

  void RemoveEntity(const IEntity& ett) {
    typename ThreadingModel::Lock lock(*this);
    assert(!ett.IsActive() && "entity must not be active");
    entity_pool_.Recall(ett);
  }

  void RemoveInactiveEntities() {
    entities_.erase(std::remove_if(entities_.begin(), entities_.end(),
                                   [](auto ett) { return ett.IsActive(); }),
                    entities_.end());
  }

  const ComponentPoolManager& GetComponentPoolManager() const {
    return component_pool_manager_;
  }

  ComponentPoolManager& GetComponentPoolManager() {
    return component_pool_manager_;
  }

  const SingletonComponentManager& GetSingletonComponentManager() const {
    return singleton_component_manager_;
  }

  SingletonComponentManager& GetSingletonComponentManager() {
    return singleton_component_manager_;
  }

  template <typename... Ts>
  void GetMatchingComponentsEntities(ComponentEntityBuffer<Ts...>& dest) const {
    const auto& mask = detail::GetComponentMask<Ts...>();
    for (IEntity& ett : entities_) {
      if ((ett.GetComponentMask() & mask) == mask) {
        dest.GetComponents().emplace_back(ett.GetComponent<Ts>()...);
        dest.GetEntities().emplace_back(ett);
      }
    }
  }

 private:
  using EntitySet = std::vector<std::reference_wrapper<IEntity>>;

  IEntityPool& entity_pool_;
  ComponentPoolManager& component_pool_manager_;
  SingletonComponentManager& singleton_component_manager_;

  EntitySet entities_;
};

}  // namespace einu
