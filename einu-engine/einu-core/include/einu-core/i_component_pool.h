#pragma once

#include <functional>
#include <memory>

#include "einu-core/internal/xnent_type_id.h"
#include "einu-core/pool_policy.h"
#include "einu-core/xnent.h"

namespace einu {

// TODO(Xiaoyue Chen): hide global state for user in release code
class IComponentPool {
 public:
  using size_type = std::size_t;
  template <typename Comp>
  using Policy = PoolPolicy<Comp>;

  virtual ~IComponentPool() = default;

  template <typename T>
  void AddPolicy(const Policy<T>& policy,
                 internal::XnentTypeID id = internal::GetXnentTypeID<T>()) {
    AddPolicyImpl(policy.init_size, policy.value, policy.growth_func, id);
  }

  template <typename T>
  T& Acquire(internal::XnentTypeID id = internal::GetXnentTypeID<T>()) {
    return static_cast<T&>(AcquireImpl(id));
  }

  template <typename T>
  void Release(const T& comp, internal::XnentTypeID id =
                                  internal::GetXnentTypeID<T>()) noexcept {
    ReleaseImpl(id, comp);
  }

  template <typename T>
  size_type OnePoolSize(
      internal::XnentTypeID id = internal::GetXnentTypeID<T>()) const noexcept {
    return OnePoolSizeImpl(id);
  }

 protected:
  virtual void AddPolicyImpl(size_type init_size, const Xnent& value,
                             GrowthFunc growth_func,
                             internal::XnentTypeID id) = 0;
  virtual Xnent& AcquireImpl(internal::XnentTypeID id) = 0;
  virtual void ReleaseImpl(internal::XnentTypeID id,
                           const Xnent& comp) noexcept = 0;
  virtual size_type OnePoolSizeImpl(
      internal::XnentTypeID id) const noexcept = 0;
};

}  // namespace einu