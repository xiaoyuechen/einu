#pragma once

#include <cstddef>
#include <functional>

#include "einu-core/internal/xnent_mask.h"
#include "einu-core/xnent.h"
#include "einu-core/xnent_list.h"

namespace einu {

using EID = std::size_t;

// TODO(Xiaoyue Chen): hide global state for user in release code
class IEntity {
 public:
  virtual ~IEntity() = default;

  EID GetID() const noexcept { return GetIDImpl(); }
  void Reset() noexcept { ResetImpl(); }

  template <typename ComponentList>
  bool HasComponents(ComponentList l, const internal::DynamicXnentMask& mask =
                                          internal::GetXnentMask(
                                              ComponentList{})) const noexcept {
    return HasComponentsImpl(mask);
  }

  template <typename T>
  const T& GetComponent(XnentTypeID id = GetXnentTypeID<T>()) const noexcept {
    return static_cast<const T&>(GetComponentImpl(id));
  }

  template <typename T>
  T& GetComponent(XnentTypeID id = GetXnentTypeID<T>()) noexcept {
    return static_cast<T&>(GetComponentImpl(id));
  }

  template <typename T>
  void AddComponent(T& comp, XnentTypeID id = GetXnentTypeID<T>()) {
    AddComponentImpl(id, comp);
  }

  template <typename T>
  [[nodiscard]] T& RemoveComponent(
      XnentTypeID id = GetXnentTypeID<T>()) noexcept {
    return static_cast<T&>(RemoveComponentImpl(id));
  }

 private:
  virtual EID GetIDImpl() const noexcept = 0;
  virtual void ResetImpl() noexcept = 0;
  virtual bool HasComponentsImpl(
      const internal::DynamicXnentMask& mask) const noexcept = 0;
  virtual const Xnent& GetComponentImpl(XnentTypeID id) const noexcept = 0;
  virtual Xnent& GetComponentImpl(XnentTypeID id) noexcept = 0;
  virtual void AddComponentImpl(XnentTypeID id, Xnent& comp) = 0;
  virtual Xnent& RemoveComponentImpl(XnentTypeID id) noexcept = 0;
};

}  // namespace einu