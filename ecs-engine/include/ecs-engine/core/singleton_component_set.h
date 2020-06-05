#pragma once

#include <memory>

#include "ecs-engine/core/i_singleton_component.h"

namespace ecs {

class SingletonComponentSet {
 public:
  template <typename T, typename... Args>
  T& Make(Args&&... args) {
    auto idx = rtti::GetClassIndex<T>();
    if (idx >= vec_.size()) {
      vec_.resize(idx + 1);
    }
    auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
    auto& ref = *ptr;
    vec_[idx] = std::move(ptr);
    return ref;
  }

  template <typename T>
  const T& Get() const noexcept {
    auto idx = rtti::GetClassIndex<T>();
    return static_cast<const T&>(*vec_[idx]);
  }

  template <typename T>
  T& Get() noexcept {
    return const_cast<T&>(
        static_cast<const SingletonComponentSet&>(*this).Get<T>());
  }

 private:
  using Ptr = std::unique_ptr<ISingletonComponent>;
  std::vector<Ptr> vec_;
};

}  // namespace ecs