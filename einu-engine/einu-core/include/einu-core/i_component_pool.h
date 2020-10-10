#pragma once

#include "einu-core/internal/xnent_type_id.h"
#include "einu-core/xnent.h"

namespace einu {

class IComponentPool {
 public:
  template <typename T>
  T& Acquire(internal::XnentTypeID id = internal::GetXnentTypeID<T>()) {
    return static_cast<T&>(AcquireImpl(id));
  }

  template <typename T>
  void Release(const T& comp, internal::XnentTypeID id =
                                  internal::GetXnentTypeID<T>()) noexcept {
    ReleaseImpl(id, comp);
  }

 protected:
  virtual Xnent& AcquireImpl(internal::XnentTypeID id) = 0;
  virtual void ReleaseImpl(internal::XnentTypeID id,
                           const Xnent& comp) noexcept = 0;
};

}  // namespace einu