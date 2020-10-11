#pragma once

#include <functional>
#include <memory>

#include "einu-core/internal/xnent_type_id.h"
#include "einu-core/xnent.h"

namespace einu {

using GrowthFunc = std::function<std::size_t(std::size_t)>;

constexpr std::size_t DefaultComponentPoolGrowFunc(
    std::size_t pool_size) noexcept {
  return pool_size == 0 ? 1 : 2 * pool_size;
}

template <typename Component>
struct ComponentPoolPolicy {
  using size_type = std::size_t;
  using value_type = Component;

  constexpr ComponentPoolPolicy(
      size_type init_size, const value_type& value = value_type{},
      GrowthFunc growth_func = DefaultComponentPoolGrowFunc) noexcept
      : init_size(init_size)
      , value(value)
      , growth_func(growth_func) {}

  size_type init_size;
  value_type value;
  GrowthFunc growth_func;
};

// TODO(Xiaoyue Chen): hide global state for user in release code
class IComponentPool {
 public:
  using size_type = std::size_t;

  virtual ~IComponentPool() = default;

  template <typename T>
  void AddPolicy(const ComponentPoolPolicy<T>& policy,
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