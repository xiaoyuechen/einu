#pragma once

#include <cstddef>
#include <functional>

#include "einu-core/internal/xnent_mask.h"
#include "einu-core/xnent.h"
#include "einu-core/xnent_list.h"

namespace einu {

using EID = std::size_t;

class IEntity {
 public:
  template <typename XnentList>
  using GetXnentMaskFunc =
      std::function<const internal::DynamicXnentMask&(XnentList)>;
  using GetXnentTypeIDFunc = std::function<internal::XnentTypeID()>;

  virtual ~IEntity() = default;

  virtual EID GetID() const noexcept = 0;

  template <typename ComponentList>
  bool HasComponents(ComponentList l,
                     GetXnentMaskFunc<ComponentList> get_xnent_mask =
                         internal::GetXnentMask<ComponentList>) const noexcept {
    return HasComponentsImpl(get_xnent_mask(l));
  }

  template <typename T>
  const T& GetComponent(GetXnentTypeIDFunc get_xnent_type_id =
                            internal::GetXnentTypeID<T>) const noexcept {
    auto id = get_xnent_type_id();
    return static_cast<const T&>(GetComponentImpl(id));
  }

  template <typename T>
  T& GetComponent(GetXnentTypeIDFunc get_xnent_type_id =
                      internal::GetXnentTypeID<T>) noexcept {
    auto id = get_xnent_type_id();
    return static_cast<T&>(GetComponentImpl(id));
  }

  template <typename T>
  void AddComponent(T& comp, GetXnentTypeIDFunc get_xnent_type_id =
                                 internal::GetXnentTypeID<T>) {
    auto id = get_xnent_type_id();
    AddComponentImpl(id, comp);
  }

  template <typename T>
  [[nodiscard]] T& RemoveComponent(GetXnentTypeIDFunc get_xnent_type_id =
                                       internal::GetXnentTypeID<T>) noexcept {
    auto id = get_xnent_type_id();
    return static_cast<T&>(RemoveComponentImpl(id));
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