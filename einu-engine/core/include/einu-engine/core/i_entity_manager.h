#pragma once

#include <vector>

#include "einu-engine/core/i_eid_pool.h"
#include "einu-engine/core/i_xnent_pool.h"
#include "einu-engine/core/internal/pool_policy.h"
#include "einu-engine/core/internal/xnent_mask.h"
#include "einu-engine/core/xnent_list.h"

namespace einu {

struct EntityBuffer {
  std::vector<Xnent*> comps;
  std::vector<EID> eids;
};

inline void Clear(EntityBuffer& buffer) noexcept {
  buffer.comps.clear();
  buffer.eids.clear();
}

class IEntityManager {
 public:
  using Policy = internal::PoolPolicy<>;

  virtual ~IEntityManager() = default;

  void SetEIDPool(IEIDPool& eid_pool) noexcept { SetEIDPoolImpl(eid_pool); }

  void SetComponentPool(IXnentPool& comp_pool) noexcept {
    SetComponentPoolImpl(comp_pool);
  }

  void SetSinglenentPool(IXnentPool& single_pool) noexcept {
    SetSinglenentPoolImpl(single_pool);
  }

  void SetPolicy(Policy policy) noexcept { SetPolicyImpl(policy); }

  [[nodiscard]] EID CreateEntity() { return CreateEntityImpl(); }

  void DestroyEntity(EID eid) { DestroyEntityImpl(eid); }

  template <typename T>
  T& AddComponent(EID eid) {
    return static_cast<T&>(AddComponentImpl(eid, GetXnentTypeID<T>()));
  }

  Xnent& AddComponent(EID eid, XnentTypeID tid) {
    return AddComponentImpl(eid, tid);
  }

  template <typename T>
  void RemoveComponent(EID eid) {
    RemoveComponentImpl(eid, GetXnentTypeID<T>());
  }

  void RemoveComponent(EID eid, XnentTypeID tid) {
    RemoveComponentImpl(eid, tid);
  }

  template <typename T>
  T& GetComponent(EID eid) {
    return static_cast<T&>(GetComponentImpl(eid, GetXnentTypeID<T>()));
  }

  Xnent& GetComponent(EID eid, XnentTypeID tid) {
    return GetComponentImpl(eid, tid);
  }

  template <typename T>
  const T& GetComponent(EID eid) const {
    return static_cast<const T&>(GetComponentImpl(eid, GetXnentTypeID<T>()));
  }

  const Xnent& GetComponent(EID eid, XnentTypeID tid) const {
    return GetComponentImpl(eid, tid);
  }

  template <typename T>
  T& AddSinglenent() {
    return static_cast<T&>(AddSinglenentImpl(GetXnentTypeID<T>()));
  }

  Xnent& AddSinglenent(XnentTypeID tid) { return AddSinglenentImpl(tid); }

  template <typename T>
  void RemoveSinglenent() {
    RemoveSinglenentImpl(GetXnentTypeID<T>());
  }

  void RemoveSinglenent(XnentTypeID tid) { RemoveSinglenentImpl(tid); }

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
  virtual void SetEIDPoolImpl(IEIDPool& eid_pool) noexcept = 0;
  virtual void SetComponentPoolImpl(IXnentPool& comp_pool) noexcept = 0;
  virtual void SetSinglenentPoolImpl(IXnentPool& single_pool) noexcept = 0;
  virtual void SetPolicyImpl(Policy policy) noexcept = 0;

  virtual EID CreateEntityImpl() = 0;
  virtual void DestroyEntityImpl(EID eid) = 0;

  virtual Xnent& AddComponentImpl(EID eid, XnentTypeID tid) = 0;
  virtual void RemoveComponentImpl(EID eid, XnentTypeID tid) = 0;
  virtual Xnent& GetComponentImpl(EID eid, XnentTypeID tid) = 0;
  virtual const Xnent& GetComponentImpl(EID eid, XnentTypeID tid) const = 0;

  virtual Xnent& AddSinglenentImpl(XnentTypeID tid) = 0;
  virtual void RemoveSinglenentImpl(XnentTypeID tid) = 0;
  virtual Xnent& GetSinglenentImpl(XnentTypeID tid) noexcept = 0;
  virtual const Xnent& GetSinglenentImpl(XnentTypeID tid) const noexcept = 0;

  virtual void GetEntitiesWithComponentsImpl(
      EntityBuffer& buffer, const internal::DynamicXnentMask& mask) = 0;

  virtual void ResetImpl() noexcept = 0;
};

}  // namespace einu