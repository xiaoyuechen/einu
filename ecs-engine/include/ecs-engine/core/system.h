#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <tuple>
#include <vector>

#include "ecs-engine/core/component_manager.h"
#include "ecs-engine/core/component_setting.h"
#include "ecs-engine/core/entity_id_manager.h"
#include "ecs-engine/utility/type_mapping.h"

namespace ecs {

template <typename... Ts>
using RequiredComponentList = ComponentList<Ts...>;

template <typename EntityManager, typename RequiredComponentList>
class System {
 public:
  using ComponentTuple = typename TupleRefOf<RequiredComponentList>::Type;
  using ComponentTupleBuffer = std::vector<ComponentTuple>;

  System(EntityManager& ett_mgr);

  const std::vector<ComponentTuple>& GetMatchingComponentTuples() const;
  std::vector<ComponentTuple>& GetMatchingComponentTuples();

  const typename EntityManager::EntityHandle GetEntityHandle(
      const ComponentTuple& tuple) const;
  typename EntityManager::EntityHandle GetEntityHandle(
      const ComponentTuple& tuple);

  const EntityManager& GetEntityManager() const;
  EntityManager& GetEntityManager();

 private:
  EntityManager& ett_mgr_;
  mutable ComponentTupleBuffer matching_comps_;
  mutable std::vector<EntityID> eid_arr_;
};

//////////////////////////////////////////////////////////////////////////

template <typename EntityManager, typename RequiredComponentList>
inline System<EntityManager, RequiredComponentList>::System(
    EntityManager& ett_mgr)
    : ett_mgr_(ett_mgr) {
  ett_mgr_.RegisterInterest(Type2Type<RequiredComponentList>{});
}

template <typename EntityManager, typename RequiredComponentList>
const typename System<EntityManager,
                      RequiredComponentList>::ComponentTupleBuffer&
System<EntityManager, RequiredComponentList>::GetMatchingComponentTuples()
    const {
  ett_mgr_.GetMatchingComponents(&matching_comps_, &eid_arr_);
  return matching_comps_;
}

template <typename EntityManager, typename RequiredComponentList>
typename System<EntityManager, RequiredComponentList>::ComponentTupleBuffer&
System<EntityManager, RequiredComponentList>::GetMatchingComponentTuples() {
  return const_cast<ComponentTupleBuffer&>(
      static_cast<const System&>(*this).GetMatchingComponentTuples());
}

template <typename EntityManager, typename RequiredComponentList>
const typename EntityManager::EntityHandle
System<EntityManager, RequiredComponentList>::GetEntityHandle(
    const ComponentTuple& tuple) const {
  auto index = &tuple - matching_comps_.data();
  const auto& eid = eid_arr_[index];
  return EntityManager::EntityHandle(eid, ett_mgr_);
}

template <typename EntityManager, typename RequiredComponentList>
typename EntityManager::EntityHandle
System<EntityManager, RequiredComponentList>::GetEntityHandle(
    const ComponentTuple& tuple) {
  const auto handle = static_cast<const System&>(*this).GetEntityHandle(tuple);
  return *const_cast<typename EntityManager::EntityHandle*>(&handle);
}

template <typename EntityManager, typename RequiredComponentList>
inline const EntityManager&
System<EntityManager, RequiredComponentList>::GetEntityManager() const {
  return ett_mgr_;
}

template <typename EntityManager, typename RequiredComponentList>
inline EntityManager&
System<EntityManager, RequiredComponentList>::GetEntityManager() {
  return const_cast<EntityManager&>(
      static_cast<const System&>(*this).GetEntityManager());
}

}  // namespace ecs

#endif  // SYSTEM_H_
