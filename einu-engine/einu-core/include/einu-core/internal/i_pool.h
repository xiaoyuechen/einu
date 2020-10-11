#pragma once

#include <cstddef>

namespace einu {
namespace internal {

template <typename Pooled, typename PoolPolicy>
class IPool {
 public:
  using size_type = std::size_t;
  using Policy = PoolPolicy;

  virtual ~IPool() = default;

  void SetPolicy(const Policy& policy) { SetPolicyImpl(policy); }
  Pooled& Acquire() { return AcquireImpl(); }
  void Release(const Pooled& ett) noexcept { ReleaseImpl(ett); }
  size_type Size() const noexcept { return SizeImpl(); }

 private:
  virtual void SetPolicyImpl(const Policy& policy) = 0;
  virtual Pooled& AcquireImpl() = 0;
  virtual void ReleaseImpl(const IEntity& ett) noexcept = 0;
  virtual size_type SizeImpl() const noexcept = 0;
};

}  // namespace internal
}  // namespace einu