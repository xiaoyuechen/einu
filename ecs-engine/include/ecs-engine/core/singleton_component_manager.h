#pragma once

#include <array>
#include <cstddef>
#include <memory>

namespace ecs {

template <std::size_t component_count>
class SingletonComponentManager {
 public:
  template <typename T>
  const T& GetSingletonComponent() const noexcept {
    auto idx = GetClassIndex<T>();
    return static_cast<const T&>(*components_[idx]);
  }

  template <typename T>
  T& GetSingletonComponent() noexcept {
    return const_cast<T&>(static_cast<const SingletonComponentManager&>(*this)
                              .GetSingletonComponent<T>());
  }

  template <typename T, typename... Args>
  T& MakeSingletonComponent(Args&&... args) {
    auto idx = GetClassIndex<T>();
    auto comp = std::make_unique<T>(std::forward<Args>()...);
    auto& ref = *comp;
    components_[idx] = std::move(comp);
    return ref;
  }

 private:
  using ComponentPtr = std::unique_ptr<IComponent>;
  using ComponentArray = std::array<ComponentPtr, component_count>;
  ComponentArray components_;
};

}  // namespace ecs