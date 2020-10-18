#pragma once

#include <functional>
#include <memory>

#include "einu-core/xnent_type_id.h"
#include "einu-core/pool_policy.h"
#include "einu-core/xnent.h"

namespace einu {

// TODO(Xiaoyue Chen): hide global state for user in release code
class IXnentPool {
 public:
  using size_type = std::size_t;
  template <typename Xnent>
  using Policy = PoolPolicy<Xnent>;

  virtual ~IXnentPool() = default;

  template <typename T>
  void AddPolicy(const Policy<T>& policy,
                 XnentTypeID id = GetXnentTypeID<T>()) {
    AddPolicyImpl(policy.init_size, policy.value, policy.growth_func, id);
  }

  template <typename T>
  T& Acquire(XnentTypeID id = GetXnentTypeID<T>()) {
    return static_cast<T&>(AcquireImpl(id));
  }

  template <typename T>
  void Release(const T& comp, XnentTypeID id =
                                  GetXnentTypeID<T>()) noexcept {
    ReleaseImpl(id, comp);
  }

  template <typename T>
  size_type OnePoolSize(
      XnentTypeID id = GetXnentTypeID<T>()) const noexcept {
    return OnePoolSizeImpl(id);
  }

 protected:
  virtual void AddPolicyImpl(size_type init_size, const Xnent& value,
                             GrowthFunc growth_func,
                             XnentTypeID id) = 0;
  virtual Xnent& AcquireImpl(XnentTypeID id) = 0;
  virtual void ReleaseImpl(XnentTypeID id,
                           const Xnent& comp) noexcept = 0;
  virtual size_type OnePoolSizeImpl(
      XnentTypeID id) const noexcept = 0;
};

}  // namespace einu