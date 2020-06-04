#pragma once

#include "ecs-engine/core/entity_id.h"
#include "ecs-engine/core/i_component.h"
#include "ecs-engine/core/i_singleton_component.h"
#include "ecs-engine/utility/rtti/class_index.h"
#include "ecs-engine/utility/tmp/type_mapping.h"

namespace ecs {

class EntityHandle {};

class IEntityManager {
 public:
  virtual std::size_t GetEntityCount() const noexcept = 0;

  virtual bool IsEntityIDValid(const EntityID& eid) const = 0;

  // const Entity& GetEntity(const EntityID& eid) const;
  // Entity& GetEntity(const EntityID& eid);

  virtual void DestroyEntity(const EntityID& eid) = 0;

  virtual const ISingletonComponent& GetSingletonComponent(
      rtti::ClassIndex idx) const = 0;
  virtual ISingletonComponent& GetSingletonComponent(rtti::ClassIndex idx) = 0;

  virtual const IComponent& GetComponent(const EntityID& eid,
                                         rtti::ClassIndex) = 0;
  virtual IComponent& AddComponent(const EntityID& eid,
                                   rtti::ClassIndex idx) = 0;
  virtual void RemoveComponent(const EntityID& eid, rtti::ClassIndex idx) = 0;
};

template <typename ComponentMask, typename ThreadingModel>
class EntityManagerImpl {


};










class EntityManagerTemplated {
 public:
  template <typename T>
  const T& GetSingletonComponent() const {
    return static_cast<const T&>(
        mgr_.GetSingletonComponent(rtti::GetClassIndex<T>()));
  }

  template <typename T>
  T& GetSingletonComponent() {
    return static_cast<T&>(
        mgr_.GetSingletonComponent(rtti::GetClassIndex<T>()));
  }

  template <typename T>
  const T& GetComponent(const EntityID& eid) const {
    return mgr_.GetComponent(eid, rtti::GetClassIndex());
  }

  template <typename T>
  T& GetComponent(const EntityID& eid) {
    return const_cast<T&>(
        static_cast<const EntityManagerTemplated&>(*this).GetComponent<T>());
  }

  template <typename T>
  T& AddComponent(const EntityID& eid) {
    return mgr_.AddComponent(eid, rtti::GetClassIndex<T>());
  }

  template <typename T>
  void RemoveComponent(const EntityID& eid);
  template <typename T>
  bool HasComponent(const EntityID& eid) const;

  template <typename... Ts>
  void GetMatchingComponents(std::vector<std::tuple<Ts&...>>* tuple_dest,
                             std::vector<EntityID>* eid_dest);

  template <typename... Ts>
  void RegisterInterest(tmp::Type2Type<ComponentList<Ts...>>);

 private:
  IEntityManager& mgr_;
};

}  // namespace ecs