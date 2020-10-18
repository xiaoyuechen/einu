#pragma once

#include <einu-rtti/type_id.h>

#include <cassert>
#include <type_traits>

#include "einu-core/xnent.h"

namespace einu {

class XnentTypeID : public rtti::TypeID {
 public:
  using rtti::TypeID::TypeID;
};

template <typename T>
void SetXnentTypeID(XnentTypeID id) noexcept {
  static_assert(std::is_base_of<Xnent, T>::value &&
                "<Xnent> must be base of <T>");
  assert(!rtti::IsAssigned(GetXnentTypeID<T>()) &&
         "xnent id is already assigned");
  rtti::SetTypeID<T>(id);
}

template <typename T>
XnentTypeID GetXnentTypeID() noexcept {
  static_assert(std::is_base_of<Xnent, T>::value &&
                "<Xnent> must be base of <T>");
  return XnentTypeID(rtti::GetTypeID<T>());
}

template <typename T>
void ResetXnentTypeID() noexcept {
  static_assert(std::is_base_of<Xnent, T>::value &&
                "<Xnent> must be base of <T>");
  rtti::SetTypeID<T>(XnentTypeID{0});
}

}  // namespace einu