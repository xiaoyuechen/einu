#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <tuple>
#include <vector>

#include "ecs-engine/core/component_manager.h"
#include "ecs-engine/core/component_setting.h"

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

 private:
  EntityManager& ett_mgr_;
  mutable ComponentTupleBuffer matching_comps_;
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
  ett_mgr_.GetMatchingComponents(matching_comps_);
  return matching_comps_;
}

template <typename EntityManager, typename RequiredComponentList>
typename System<EntityManager, RequiredComponentList>::ComponentTupleBuffer&
System<EntityManager, RequiredComponentList>::GetMatchingComponentTuples() {
  ett_mgr_.GetMatchingComponents(matching_comps_);
  return matching_comps_;
}

}  // namespace ecs

#endif  // SYSTEM_H_
