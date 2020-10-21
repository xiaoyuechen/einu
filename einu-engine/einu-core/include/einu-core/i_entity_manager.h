#pragma once

#include "einu-core/i_entity.h"
#include "einu-core/i_xnent_pool.h"
#include "einu-core/pool_policy.h"
#include "einu-core/xnent_list.h"

namespace einu {

struct EntityBuffer {
  std::vector<Xnent*> comps;
  std::vector<EID> eids;
};

inline void Clear(EntityBuffer& buffer) noexcept {
  buffer.comps.clear();
  buffer.eids.clear();
}

template <typename ComponentList>
struct EntityView;

template <typename... Ts>
class EntityView<XnentList<Ts...>> {
 public:
 private:
  EntityBuffer ett_buffer_;
};

class IEntityManager {
 public:
  using Policy = PoolPolicy<>;

  void SetComponentPool(IXnentPool& comp_pool) noexcept {
    SetComponentPoolImpl(comp_pool);
  }

  void SetPolicy(Policy policy) noexcept { SetPolicyImpl(policy); }

  [[nodiscard]] EID CreateEntity() { return CreateEntityImpl(); }

  void DestroyEntity(EID eid) noexcept { DestroyEntityImpl(eid); }

  template <typename T>
  T& AddComponent(EID eid) {
    return static_cast<T&>(AddComponentImpl(eid, GetXnentTypeID<T>()));
  }

  Xnent& AddComponent(EID eid, XnentTypeID tid) {
    return AddComponentImpl(eid, tid);
  }

  template <typename T>
  void RemoveComponent(EID eid) noexcept {
    RemoveComponentImpl(eid, GetXnentTypeID<T>());
  }

  void RemoveComponent(EID eid, XnentTypeID tid) noexcept {
    RemoveComponentImpl(eid, tid);
  }

  template <typename T>
  T& GetComponent(EID eid) noexcept {
    return static_cast<T&>(GetComponentImpl(eid, GetXnentTypeID<T>()));
  }

  Xnent& GetComponent(EID eid, XnentTypeID tid) noexcept {
    return GetComponentImpl(eid, tid);
  }

  template <typename T>
  const T& GetComponent(EID eid) const noexcept {
    return static_cast<const T&>(GetComponentImpl(eid, GetXnentTypeID<T>()));
  }

  const Xnent& GetComponent(EID eid, XnentTypeID tid) const noexcept {
    return GetComponentImpl(eid, tid);
  }

  template <typename T>
  void SetSinglenent(const T& singlenent) {
    SetSinglenentImpl(singlenent, GetXnentTypeID<T>());
  }

  void SetSinglenent(const Xnent& singlenent, XnentTypeID tid) {
    SetSinglenentImpl(singlenent, tid);
  }

  template <typename T>
  T& GetSinglenent() noexcept {
    return static_cast<const T&>(GetSinglenentImpl(GetXnentTypeID<T>()));
  }

  Xnent& GetSinglenent(XnentTypeID tid) noexcept {
    return GetSinglenentImpl(tid);
  }

  template <typename T>
  const T& GetSinglenent() const noexcept {
    return static_cast<const T&>(GetSinglenentImpl(GetXnentTypeID<T>()));
  }

  const Xnent& GetSinglenent(XnentTypeID tid) const noexcept {
    return GetSinglenentImpl(tid);
  }

  template <typename ComponentList>
  void GetEntitiesWithComponents(EntityBuffer& buffer,
                                 ComponentList comp_list) {
    GetEntitiesWithComponentsImpl(buffer, internal::GetXnentMask(comp_list));
  }

  void GetEntitiesWithComponents(EntityBuffer& buffer,
                                 const internal::DynamicXnentMask& mask) {
    GetEntitiesWithComponentsImpl(buffer, mask);
  }

  void Reset() noexcept { ResetImpl(); }

 private:
  virtual void SetComponentPoolImpl(IXnentPool& comp_pool) noexcept = 0;
  virtual void SetPolicyImpl(Policy policy) noexcept = 0;

  virtual EID CreateEntityImpl() = 0;
  virtual void DestroyEntityImpl(EID eid) noexcept = 0;

  virtual Xnent& AddComponentImpl(EID eid, XnentTypeID tid) = 0;
  virtual void RemoveComponentImpl(EID eid, XnentTypeID tid) noexcept = 0;
  virtual Xnent& GetComponentImpl(EID eid, XnentTypeID tid) noexcept = 0;
  virtual const Xnent& GetComponentImpl(EID eid,
                                        XnentTypeID tid) const noexcept = 0;

  virtual void SetSinglenentImpl(const Xnent& singlenent, XnentTypeID tid) = 0;
  virtual Xnent& GetSinglenentImpl(XnentTypeID tid) noexcept = 0;
  virtual const Xnent& GetSinglenentImpl(XnentTypeID tid) const noexcept = 0;

  virtual void GetEntitiesWithComponentsImpl(
      EntityBuffer& buffer, const internal::DynamicXnentMask& mask) = 0;

  virtual void ResetImpl() noexcept = 0;
};

}  // namespace einu