// Copyright (C) 2020  Xiaoyue Chen
//
// This file is part of EINU Engine.
// See <https://github.com/xiaoyuechen/einu.git>.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <vector>

#include "einu-engine/core/i_eid_pool.h"
#include "einu-engine/core/i_xnent_pool.h"
#include "einu-engine/core/internal/pool_policy.h"
#include "einu-engine/core/internal/xnent_mask.h"
#include "einu-engine/core/xnent_list.h"

#ifdef EINU_CORE_PROFILE
#include "easy/profiler.h"
#endif

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
  using Policy = internal::PoolPolicy;

  virtual ~IEntityManager() = default;

  void SetEIDPool(IEIDPool& eid_pool) noexcept { SetEIDPoolImpl(eid_pool); }

  void SetComponentPool(IXnentPool& comp_pool) noexcept {
    SetComponentPoolImpl(comp_pool);
  }

  void SetSinglenentPool(IXnentPool& single_pool) noexcept {
    SetSinglenentPoolImpl(single_pool);
  }

  void SetPolicy(Policy policy) noexcept { SetPolicyImpl(policy); }

  EID CreateEntity() {
#ifdef EINU_CORE_PROFILE
    EASY_FUNCTION();
#endif
    return CreateEntityImpl();
  }

  void DestroyEntity(EID eid) {
#ifdef EINU_CORE_PROFILE
    EASY_FUNCTION();
#endif
    DestroyEntityImpl(eid);
  }

  bool ContainsEntity(EID eid) const {
#ifdef EINU_CORE_PROFILE
    EASY_FUNCTION();
#endif
    return ContainsEntityImpl(eid);
  }

  template <typename T>
  T& AddComponent(EID eid) {
#ifdef EINU_CORE_PROFILE
    EASY_FUNCTION();
#endif
    return static_cast<T&>(AddComponentImpl(eid, GetXnentTypeID<T>()));
  }

  Xnent& AddComponent(EID eid, XnentTypeID tid) {
#ifdef EINU_CORE_PROFILE
    EASY_FUNCTION();
#endif
    return AddComponentImpl(eid, tid);
  }

  template <typename T>
  void RemoveComponent(EID eid) {
#ifdef EINU_CORE_PROFILE
    EASY_FUNCTION();
#endif
    RemoveComponentImpl(eid, GetXnentTypeID<T>());
  }

  void RemoveComponent(EID eid, XnentTypeID tid) {
#ifdef EINU_CORE_PROFILE
    EASY_FUNCTION();
#endif
    RemoveComponentImpl(eid, tid);
  }

  template <typename T>
  T& GetComponent(EID eid) {
#ifdef EINU_CORE_PROFILE
    EASY_FUNCTION();
#endif
    return static_cast<T&>(GetComponentImpl(eid, GetXnentTypeID<T>()));
  }

  Xnent& GetComponent(EID eid, XnentTypeID tid) {
#ifdef EINU_CORE_PROFILE
    EASY_FUNCTION();
#endif
    return GetComponentImpl(eid, tid);
  }

  template <typename T>
  const T& GetComponent(EID eid) const {
#ifdef EINU_CORE_PROFILE
    EASY_FUNCTION();
#endif
    return static_cast<const T&>(GetComponentImpl(eid, GetXnentTypeID<T>()));
  }

  const Xnent& GetComponent(EID eid, XnentTypeID tid) const {
#ifdef EINU_CORE_PROFILE
    EASY_FUNCTION();
#endif
    return GetComponentImpl(eid, tid);
  }

  template <typename T>
  T& AddSinglenent() {
#ifdef EINU_CORE_PROFILE
    EASY_FUNCTION();
#endif
    return static_cast<T&>(AddSinglenentImpl(GetXnentTypeID<T>()));
  }

  Xnent& AddSinglenent(XnentTypeID tid) {
#ifdef EINU_CORE_PROFILE
    EASY_FUNCTION();
#endif
    return AddSinglenentImpl(tid);
  }

  template <typename T>
  void RemoveSinglenent() {
#ifdef EINU_CORE_PROFILE
    EASY_FUNCTION();
#endif
    RemoveSinglenentImpl(GetXnentTypeID<T>());
  }

  void RemoveSinglenent(XnentTypeID tid) {
#ifdef EINU_CORE_PROFILE
    EASY_FUNCTION();
#endif
    RemoveSinglenentImpl(tid);
  }

  template <typename T>
  T& GetSinglenent() noexcept {
#ifdef EINU_CORE_PROFILE
    EASY_FUNCTION();
#endif
    return static_cast<T&>(GetSinglenentImpl(GetXnentTypeID<T>()));
  }

  Xnent& GetSinglenent(XnentTypeID tid) noexcept {
#ifdef EINU_CORE_PROFILE
    EASY_FUNCTION();
#endif
    return GetSinglenentImpl(tid);
  }

  template <typename T>
  const T& GetSinglenent() const noexcept {
#ifdef EINU_CORE_PROFILE
    EASY_FUNCTION();
#endif
    return static_cast<const T&>(GetSinglenentImpl(GetXnentTypeID<T>()));
  }

  const Xnent& GetSinglenent(XnentTypeID tid) const noexcept {
#ifdef EINU_CORE_PROFILE
    EASY_FUNCTION();
#endif
    return GetSinglenentImpl(tid);
  }

  template <typename ComponentList>
  void GetEntitiesWithComponents(EntityBuffer& buffer,
                                 ComponentList comp_list) {
#ifdef EINU_CORE_PROFILE
    EASY_FUNCTION();
#endif
    GetEntitiesWithComponentsImpl(buffer, internal::GetXnentMask(comp_list),
                                  internal::GetXnentTypeIDArray(comp_list));
  }

  void GetEntitiesWithComponents(EntityBuffer& buffer,
                                 const internal::DynamicXnentMask& mask,
                                 const internal::XnentTypeIDArray& xtid_arr) {
#ifdef EINU_CORE_PROFILE
    EASY_FUNCTION();
#endif
    GetEntitiesWithComponentsImpl(buffer, mask, xtid_arr);
  }

  void Reset() noexcept { ResetImpl(); }

 private:
  virtual void SetEIDPoolImpl(IEIDPool& eid_pool) noexcept = 0;
  virtual void SetComponentPoolImpl(IXnentPool& comp_pool) noexcept = 0;
  virtual void SetSinglenentPoolImpl(IXnentPool& single_pool) noexcept = 0;
  virtual void SetPolicyImpl(Policy policy) noexcept = 0;

  virtual EID CreateEntityImpl() = 0;
  virtual void DestroyEntityImpl(EID eid) = 0;
  virtual bool ContainsEntityImpl(EID eid) const = 0;

  virtual Xnent& AddComponentImpl(EID eid, XnentTypeID tid) = 0;
  virtual void RemoveComponentImpl(EID eid, XnentTypeID tid) = 0;
  virtual Xnent& GetComponentImpl(EID eid, XnentTypeID tid) = 0;
  virtual const Xnent& GetComponentImpl(EID eid, XnentTypeID tid) const = 0;

  virtual Xnent& AddSinglenentImpl(XnentTypeID tid) = 0;
  virtual void RemoveSinglenentImpl(XnentTypeID tid) = 0;
  virtual Xnent& GetSinglenentImpl(XnentTypeID tid) noexcept = 0;
  virtual const Xnent& GetSinglenentImpl(XnentTypeID tid) const noexcept = 0;

  virtual void GetEntitiesWithComponentsImpl(
      EntityBuffer& buffer, const internal::DynamicXnentMask& mask,
      const internal::XnentTypeIDArray& xtid_arr) = 0;

  virtual void ResetImpl() noexcept = 0;
};

}  // namespace einu
