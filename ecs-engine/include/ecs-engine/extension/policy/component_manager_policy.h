#pragma once

#include <cassert>

#include "ecs-engine/core/component_manager.h"
#include "ecs-engine/core/component_setting.h"
#include "ecs-engine/utility/type_mapping.h"

namespace ecs {

template <typename ComponentSetting, typename ThreadingModel>
class ComponentManagerPolicy {
 public:
  template <typename T>
  using ComponentManager = ComponentManager<T, ThreadingModel>;

  class Builder;

  template <typename T>
  const ComponentManager<T>& GetComponentManager(Type2Type<T>) const noexcept;
  template <typename T>
  ComponentManager<T>& GetComponentManager(Type2Type<T>) noexcept;

  template <typename T>
  const T& GetSingletonComponent() const noexcept;
  template <typename T>
  T& GetSingletonComponent() noexcept;

 private:
  using ManagerList =
      typename ListWrapperOf<ComponentManager,
                             typename ComponentSetting::Components>::Type;

  using SingletonComponentList = typename ComponentSetting::SingletonComponents;

  using ManagerPtrTuple =
      typename TupleWrapperOf<std::unique_ptr, ManagerList>::Type;
  using SingletonCompPtrTuple =
      typename ecs::TupleWrapperOf<std::unique_ptr,
                                   SingletonComponentList>::Type;

  ManagerPtrTuple manager_ptr_tup_;
  SingletonCompPtrTuple singleton_comp_tup_;
};

template <typename ComponentSetting, typename ThreadingModel>
class ComponentManagerPolicy<ComponentSetting, ThreadingModel>::Builder {
 public:
  template <typename T, typename... Args>
  T& MakeComponentManager(Args&&... args);

  template <typename T, typename... Args>
  T& MakeSingletonComponent(Args&&... args);

  ComponentManagerPolicy Build();

 private:
  ComponentManagerPolicy::ManagerPtrTuple manager_ptr_tup_;
  ComponentManagerPolicy::SingletonCompPtrTuple singleton_comp_tup_;
};

//////////////////////////////////////////////////////////////////////////

template <typename ComponentSetting, typename ThreadingModel>
template <typename T>
inline const typename ComponentManagerPolicy<
    ComponentSetting, ThreadingModel>::template ComponentManager<T>&
ComponentManagerPolicy<ComponentSetting, ThreadingModel>::GetComponentManager(
    Type2Type<T>) const noexcept {
  return *std::get<std::unique_ptr<ComponentManager<T>>>(manager_ptr_tup_);
}

template <typename ComponentSetting, typename ThreadingModel>
template <typename T>
inline typename ComponentManagerPolicy<
    ComponentSetting, ThreadingModel>::template ComponentManager<T>&
ComponentManagerPolicy<ComponentSetting, ThreadingModel>::GetComponentManager(
    Type2Type<T>) noexcept {
  return const_cast<ComponentManager<T>&>(
      static_cast<const ComponentManagerPolicy&>(*this)
          .GetComponentManager<T>());
}

template <typename ComponentSetting, typename ThreadingModel>
template <typename T>
inline const T& ComponentManagerPolicy<
    ComponentSetting, ThreadingModel>::GetSingletonComponent() const noexcept {
  return *std::get<std::unique_ptr<T>>(singleton_comp_tup_);
}

template <typename ComponentSetting, typename ThreadingModel>
template <typename T>
inline T& ComponentManagerPolicy<
    ComponentSetting, ThreadingModel>::GetSingletonComponent() noexcept {
  return const_cast<T&>(static_cast<const ComponentManagerPolicy&>(*this)
                            .GetSingletonComponent<T>());
}

template <typename ComponentSetting, typename ThreadingModel>
template <typename T, typename... Args>
inline T& ComponentManagerPolicy<ComponentSetting, ThreadingModel>::Builder::
    MakeComponentManager(Args&&... args) {
  auto mgr = std::make_unique<T>(std::forward<Args>(args)...);
  auto& ref = *mgr;
  std::get<std::unique_ptr<T>>(manager_ptr_tup_) = std::move(mgr);
  return ref;
}

template <typename ComponentSetting, typename ThreadingModel>
template <typename T, typename... Args>
inline T& ComponentManagerPolicy<ComponentSetting, ThreadingModel>::Builder::
    MakeSingletonComponent(Args&&... args) {
  auto singleton_comp = std::make_unique<T>(std::forward<Args>(args)...);
  auto& ref = *singleton_comp;
  std::get<std::unique_ptr<T>>(singleton_comp_tup_) = std::move(singleton_comp);
  return ref;
}

namespace detail {

template <typename PtrTuple>
bool PtrTupleHasNull(const PtrTuple& tup) {
  bool has_null = false;
  ecs::algo::StaticFor<std::tuple_size<PtrTuple>::value>([&](auto i) {
    if (!std::get<i>(tup)) {
      has_null = true;
      return;
    }
  });
  return has_null;
}

}  // namespace detail

template <typename ComponentSetting, typename ThreadingModel>
inline ComponentManagerPolicy<ComponentSetting, ThreadingModel>
ComponentManagerPolicy<ComponentSetting, ThreadingModel>::Builder::Build() {
  assert(
      !detail::PtrTupleHasNull(manager_ptr_tup_) &&
      "Failed to build component manager policy. Component manager not set.");
  assert(
      !detail::PtrTupleHasNull(singleton_comp_tup_) &&
      "Failed to build component manager policy. Singleton component not set.");

  auto policy = ComponentManagerPolicy{};
  policy.manager_ptr_tup_ = std::move(manager_ptr_tup_);
  policy.singleton_comp_tup_ = std::move(singleton_comp_tup_);
  return policy;
}

}  // namespace ecs