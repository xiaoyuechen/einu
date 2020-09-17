#pragma once

#include <map>

#include "ecs-engine/core/component_map.h"
#include "ecs-engine/core/component_mask.h"
#include "ecs-engine/core/i_component.h"
#include "ecs-engine/extension/policy/threading_model.h"
#include "ecs-engine/utility/rtti/class_index_storage.h"

namespace ecs {

class IEntity {
 public:
  template <typename T>
  bool HasComponent() const {
    return HasComponent(rtti::GetClassIndex<T>());
  }

  template <typename T>
  const T& GetComponent() const {
    return static_cast<const T&>(GetComponent(rtti::GetClassIndex<T>()));
  }

  template <typename T>
  T& GetComponent() {
    return static_cast<T&>(GetComponent(rtti::GetClassIndex<T>()));
  }

  template <typename T>
  T& AddComponent() {
    return static_cast<T&>(AddComponent(rtti::GetClassIndex<T>()));
  }

  template <typename T>
  void RemoveComponent() {
    RemoveComponent(rtti::GetClassIndex<T>());
  }

  virtual bool IsActive() const = 0;
  virtual void Destroy() = 0;
  virtual const ComponentMask& GetComponentMask() const = 0;
  virtual const ComponentMap& GetComponentMap() const = 0;

 protected:
  virtual bool HasComponent(rtti::ClassIndex idx) const = 0;
  virtual const IComponent& GetComponent(rtti::ClassIndex idx) const = 0;
  virtual IComponent& GetComponent(rtti::ClassIndex idx) = 0;

  virtual IComponent& AddComponent(rtti::ClassIndex idx) = 0;
  virtual void RemoveComponent(rtti::ClassIndex idx) = 0;
};

template <typename EntityManagerType, typename ThreadingModel = MultiThreaded>
class Entity : public ThreadingModel, public IEntity {
 public:
  using EntityManager = EntityManagerType;

  virtual bool IsActive() const noexcept override {
    return component_mask_->any();
  }

  virtual void Destroy() override {
    typename ThreadingModel::Lock lock(*this);
    auto& component_pool_manager = entity_manager_->GetComponentPoolManager();
    for (auto&& [idx, comp] : *component_map_) {
      auto& pool = component_pool_manager.Get(idx);
      pool.Recall(*comp);
    }
    component_mask_->reset();
    component_map_->clear();
    entity_manager_->RemoveEntity(*this);
  }

  virtual const ComponentMask& GetComponentMask() const override {
    return *component_mask_;
  }

  virtual const ComponentMap& GetComponentMap() const override {
    return *component_map_;
  }

 protected:
  virtual bool HasComponent(rtti::ClassIndex idx) const override {
    return component_mask_->test(idx);
  }

  virtual const IComponent& GetComponent(rtti::ClassIndex idx) const override {
    return *component_map_->at(idx);
  }

  virtual IComponent& GetComponent(rtti::ClassIndex idx) {
    return *component_map_->at(idx);
  }

  virtual IComponent& AddComponent(rtti::ClassIndex idx) override {
    typename ThreadingModel::Lock lock(*this);
    assert(!component_mask_->test(idx) && "entity already has <T> component");
    component_mask_->set(idx);
    auto& component_pool_manager = entity_manager_->GetComponentPoolManager();
    auto& component_pool = component_pool_manager.Get(idx);
    auto& comp = component_pool.Acquire();
    (*component_map_)[idx] = &comp;
    return comp;
  }

  virtual void RemoveComponent(rtti::ClassIndex idx) override {
    typename ThreadingModel::Lock lock(*this);
    assert(component_mask_->test(idx) && "entity dose not have <T> component");
    component_mask_->reset(idx);
    auto& comp = *component_map_->at(idx);
    component_map_->erase(idx);
    auto& component_pool_manager = entity_manager_->GetComponentPoolManager();
    auto& component_pool = component_pool_manager.Get(idx);
    component_pool.Recall(comp);
    if (component_mask_->none()) {
      entity_manager_->RemoveEntity(*this);
    }
  }

 private:
  EntityManager* entity_manager_ = nullptr;
  ComponentMask* component_mask_ = nullptr;
  ComponentMap* component_map_ = nullptr;

  template <typename>
  friend class EntityPool;
};

}  // namespace ecs