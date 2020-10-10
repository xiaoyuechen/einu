#pragma once

#include "einu-core/internal/xnent_type_id.h"
#include "einu-core/xnent.h"

namespace einu {

class IComponentPool {
 public:
  template <typename T>
  T& Acquire() {
    return static_cast<T&>(AcquireImpl(GetXnentTypeID<T>()));
  }

  template <typename T>
  void Release(const T& comp) noexcept {
    ReleaseImpl(GetXnentTypeID<T>(), comp);
  }

 protected:
  virtual Xnent& AcquireImpl(internal::XnentTypeID idx) = 0;
  virtual void ReleaseImpl(internal::XnentTypeID idx,
                           const Xnent& comp) noexcept = 0;
};

}  // namespace einu