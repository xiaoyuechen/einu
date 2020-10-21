#pragma once

#include "einu-core/i_entity.h"
#include "einu-core/xnent_list.h"

namespace einu {

template <typename ComponentList>
struct EntityBuffer;

template <typename... Ts>
struct EntityBuffer<XnentList<Ts...>> {
  using ComponentTuple = std::tuple<Ts&...>;
  using ComponentArr = std::vector<ComponentTuple>;
  using EntityArr = std::vector<EID>;

  ComponentArr comps;
  EntityArr etts;
};

inline void Clear(EntityBuffer& buffer) noexcept {
  buffer.etts.clear();
  buffer.comps.clear();
}

class IEntityManager {
 public:
  [[nodiscard]] EID CreateEntity() { return CreateEntityImpl(); }

  void DestroyEntity(EID eid) noexcept { DestroyEntityImpl(eid); }

  template <typename T>
  T& AddComponent(EID eid) {
    return static_cast<T&>(AddComponentImpl(eid, GetXnentTypeID<T>()));
  }

  template <typename T>
  void RemoveComponent(EID eid) noexcept {
    RemoveComponentImpl(eid, GetXnentTypeID<T>())
  }

  template <typename T>
  T& GetComponent(EID eid) noexcept {
    return static_cast<T&>(GetComponentImpl(eid, GetXnentTypeID<T>()));
  }

  template <typename T>
  const T& GetComponent(EID eid) const noexcept {
    return static_cast<T&>(GetComponentImpl(eid, GetXnentTypeID<T>()));
  }

  template <typename ComponentList>
  void GetEntitiesWithComponents(EntityBuffer& buffer) {
    GetEntitiesWithComponents(buffer, internal::GetXnentMask(ComponentList{}));
  }

  void Reset() noexcept { ResetImpl(); }

 private:
  virtual EID CreateEntityImpl() = 0;
  virtual void DestroyEntityImpl(EID eid) noexcept = 0;
  virtual Xnent& AddComponentImpl(EID eid, XnentTypeID tid) = 0;
  virtual void RemoveComponentImpl(EID eid, XnentTypeID tid) noexcept = 0;
  virtual Xnent& GetComponentImpl(EID eid, XnentTypeID tid) noexcept = 0;
  virtual const Xnent& GetComponentImpl(EID eid,
                                        XnentTypeID tid) const noexcept = 0;
  virtual void GetEntitiesWithComponentsImpl(
      EntityBuffer& buffer, const internal::DynamicXnentMask& mask) = 0;
  virtual void Reset() = 0;
};

}  // namespace einu