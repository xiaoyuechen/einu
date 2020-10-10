#pragma once

#include <cstddef>

#include "einu-core/internal/xnent_mask.h"
#include "einu-core/xnent.h"
#include "einu-core/xnent_list.h"

namespace einu {

using EID = std::size_t;

class IEntity {
 public:
  virtual ~IEntity() = default;

  virtual EID GetID() const noexcept = 0;

  template <typename ComponentList>
  bool HasComponents(ComponentList l) const noexcept {
    return HasComponentsImpl(internal::GetXnentMask(l));
  }

  template <typename T>
  const T& GetComponent() const noexcept {
    return static_cast<const T&>(GetComponentImpl(GetXnentTypeID<T>()));
  }

  template <typename T>
  T& GetComponent() noexcept {
    return static_cast<T&>(GetComponentImpl(GetXnentTypeID<T>()));
  }

  template <typename T>
  void AddComponent(T& comp) {
    AddComponentImpl(internal::GetXnentTypeID<T>(), comp);
  }

  template <typename T>
  [[nodiscard]] T& RemoveComponent() noexcept {
    return static_cast<T&>(RemoveComponentImpl(internal::GetXnentTypeID<T>()));
  }

 protected:
  virtual bool HasComponentsImpl(
      const internal::DynamicXnentMask& mask) const noexcept = 0;
  virtual const Xnent& GetComponentImpl(
      internal::XnentTypeID idx) const noexcept = 0;
  virtual Xnent& GetComponentImpl(internal::XnentTypeID idx) noexcept = 0;
  virtual void AddComponentImpl(internal::XnentTypeID idx, Xnent& comp) = 0;
  virtual Xnent& RemoveComponentImpl(internal::XnentTypeID idx) noexcept = 0;
};

}  // namespace einu