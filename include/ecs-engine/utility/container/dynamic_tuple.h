#pragma once

#include <memory>
#include <vector>

#include "ecs-engine/utility/rtti/class_index_storage.h"

namespace ecs {

// all classes must be registered using ClassIndexRegister to use this container
template <typename Base>
class DynamicTuple {
 public:
  template <typename T, typename... Args>
  T& Make(Args&&... args) {
    auto idx = rtti::GetClassIndex<T>();
    if (idx >= vec_.size()) {
      vec_.resize(idx + 1);
    }
    auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
    auto ref = *ptr;
    vec_[idx] = std::move(ptr);
    return ref;
  }

  template <typename T>
  const T& Get() const noexcept {
    auto idx = rtti::ClassIndexStorage::value;
    return static_cast<T>(vec_[idx]);
  }

  template <typename T>
  T& Get() noexcept {
    return const_cast<T&>(static_cast<const DynamicTuple&>(*this).Get<T>());
  }

 private:
  using Ptr = std::unique_ptr<Base>;
  std::vector<Ptr> vec_;
};

}  // namespace ecs