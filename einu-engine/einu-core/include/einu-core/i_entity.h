#pragma once

#include "einu-core/xnent_list.h"
#include "einu-core/xnent.h"
#include "einu-core/internal/xnent_mask.h"

namespace einu {

using EID = std::size_t;

class IEntity {
 public:
  virtual EID GetID() const noexcept = 0;

  template <typename... Ts>
  bool HasComponents() const noexcept {
    return HasComponents(internal::GetComponentMask(ComponentList<Ts...>{}));
  }

  template <typename T>
  const T& GetComponent() const noexcept {
    return static_cast<const T&>(
        internal::GetComponent(GetXnentIndex<T>()));
  }

  template <typename T>
  T& GetComponent() noexcept {
    return static_cast<T&>(GetComponent(GetXnentIndex<T>()));
  }

  template <typename T>
  void AddComponent(T& comp) {
    AddComponent(internal::GetXnentIndex<T>(), comp);
  }

  template <typename T>
  T& RemoveComponent() noexcept {
    return static_cast<T&>(RemoveComponent(internal::GetXnentIndex<T>()));
  }

 protected:
  virtual bool HasComponents(
      const internal::XnentMask& mask) const noexcept = 0;
  virtual const Xnent& GetComponent(
      internal::XnentIndex idx) const noexcept = 0;
  virtual Xnent& GetComponent(internal::XnentIndex idx) noexcept = 0;
  virtual void AddComponent(internal::XnentIndex idx, Xnent& comp) = 0;
  virtual Xnent& RemoveComponent(
      internal::XnentIndex idx) noexcept = 0;
};

}  // namespace einu