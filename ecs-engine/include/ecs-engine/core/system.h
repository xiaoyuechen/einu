#pragma once

#include <tuple>
#include <vector>

#include "ecs-engine/core/component_context.h"
#include "ecs-engine/core/component_entity_buffer.h"
#include "ecs-engine/core/entity_manager.h"

namespace ecs {

template <typename EntityManager, typename RequiredComponentList>
class System;

template <typename EntityManager, typename... Ts>
class System<EntityManager, ComponentList<Ts...>> {
 public:
  using ComponentEntityBuffer = ComponentEntityBuffer<Ts...>;

  System(EntityManager& ett_mgr)
      : ett_mgr_(ett_mgr) {}

  virtual ~System() = default;

  void RefreshMatchingBuffer() const {
    comp_ett_buffer_.Clear();
    ett_mgr_.GetMatchingComponentsEntities<Ts...>(comp_ett_buffer_);
  }

  const EntityManager& GetEntityManager() const { return ett_mgr_; }
  EntityManager& GetEntityManager() {
    return const_cast<EntityManager&>(
        static_cast<const System&>(*this).GetEntityManager());
  }

  ComponentEntityBuffer& GetMatchingBuffer() noexcept {
    return comp_ett_buffer_;
  }

  const ComponentEntityBuffer& GetMatchingBuffer() const noexcept {
    return comp_ett_buffer_;
  }

 private:
  EntityManager& ett_mgr_;
  mutable ComponentEntityBuffer comp_ett_buffer_;
};

}  // namespace ecs