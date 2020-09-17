#pragma once

#include <vector>

#include "ecs-engine/core/component_map.h"
#include "ecs-engine/core/component_mask.h"
#include "ecs-engine/utility/free_index_stack.h"

namespace ecs {

class IEntityManager;

class IEntityPool {
 public:
  using size_type = std::size_t;
  virtual IEntity& Acquire(IEntityManager& ett_mgr) = 0;
  virtual void Recall(const IEntity& ett) = 0;
  virtual size_type Size() const noexcept = 0;
  virtual size_type FreeSize() const noexcept = 0;
};

template <typename Entity>
class EntityPool : public IEntityPool {
 public:
  EntityPool(size_type count)
      : etts_(count)
      , comp_masks_(count)
      , comp_maps_(count)
      , free_index_stack_(count) {}

  virtual IEntity& Acquire(IEntityManager& ett_mgr) override {
    auto idx = free_index_stack_.Acquire();
    auto& ett = etts_[idx];
    ett.entity_manager_ = &static_cast<Entity::EntityManager&>(ett_mgr);
    ett.component_map_ = &comp_maps_[idx];
    ett.component_mask_ = &comp_masks_[idx];
    return ett;
  }

  virtual void Recall(const IEntity& ett) override {
    auto idx = &static_cast<const Entity&>(ett) - etts_.data();
    free_index_stack_.Recall(idx);
  }

  virtual size_type Size() const noexcept override { return etts_.size(); }

  virtual size_type FreeSize() const noexcept override {
    return free_index_stack_.Size();
  }

 private:
  using Entities = std::vector<Entity>;
  using ComponentMasks = std::vector<ComponentMask>;
  using ComponentMaps = std::vector<ComponentMap>;
  using FreeIndexStack = FreeIndexStack<size_type>;

  Entities etts_;
  ComponentMasks comp_masks_;
  ComponentMaps comp_maps_;
  FreeIndexStack free_index_stack_;
};
}  // namespace ecs