#pragma once

#include "ecs-engine/utility/rtti/class_index.h"
#include "ecs-engine/utility/tmp/type_mapping.h"

namespace ecs {

class IEntityManager {
 public:
  template <typename... Ts>
  void GetMatchingComponents(std::vector<std::tuple<Ts&...>>* tuple_dest,
                             std::vector<EntityID>* eid_dest);

  template <typename... Ts>
  void RegisterInterest(tmp::Type2Type<ComponentList<Ts...>>);

  std::size_t GetEntityCount() const noexcept;

  template <typename T>
  T& AddComponent(const EntityID& eid);
  template <typename T>
  void RemoveComponent(const EntityID& eid);
  template <typename T>
  const T& GetComponent(const EntityID& eid) const;
  template <typename T>
  T& GetComponent(const EntityID& eid);
  template <typename T>
  bool HasComponent(const EntityID& eid) const;

  bool IsEntityIDValid(const EntityID& eid) const;

  // const Entity& GetEntity(const EntityID& eid) const;
  // Entity& GetEntity(const EntityID& eid);

  void DestroyEntity(const EntityID& eid);

  template <typename T>
  const T& GetSingletonComponent() const {
    return static_cast<const T&>(
        GetSingletonComponent(rtti::GetClassIndex<T>()));
  }

  template <typename T>
  T& GetSingletonComponent();

 protected:
  virtual const IComponent& GetSingletonComponent(
      rtti::ClassIndex idx) const = 0;
};

}  // namespace ecs