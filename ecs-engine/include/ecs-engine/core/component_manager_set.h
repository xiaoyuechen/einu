#pragma once

#include <memory>
#include <utility>

#include "ecs-engine/core/component_manager.h"
#include "ecs-engine/utility/rtti/class_index.h"

namespace ecs {

class ComponentManagerSet {
 public:
  template <typename T>
  using ComponentManager = ComponentManager<T>;

  template <typename T, typename... Args>
  ComponentManager<T>& Make(Args&&... args) {
    auto idx = rtti::GetClassIndex<T>();
    if (idx >= vec_.size()) {
      vec_.resize(idx + 1);
    }
    auto ptr =
        std::make_unique<ComponentManager<T>>(std::forward<Args>(args)...);
    auto& ref = *ptr;
    vec_[idx] = std::move(ptr);
    return ref;
  }

  template <typename T>
  const ComponentManager<T>& Get() const noexcept {
    auto idx = rtti::GetClassIndex<T>();
    return static_cast<const ComponentManager<T>&>(*vec_[idx]);
  }

  template <typename T>
  ComponentManager<T>& Get() noexcept {
    return const_cast<ComponentManager<T>&>(
        static_cast<const ComponentManagerSet&>(*this).Get<T>());
  }

  auto& operator[](std::size_t pos) const noexcept { return *vec_[pos]; }
  auto& operator[](std::size_t pos) noexcept { return *vec_[pos]; }

 private:
  using Ptr = std::unique_ptr<IComponentManager>;
  std::vector<Ptr> vec_;
};

}  // namespace ecs