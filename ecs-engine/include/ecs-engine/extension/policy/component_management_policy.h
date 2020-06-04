#pragma once

#include <cassert>


#include "ecs-engine/core/component_manager.h"
#include "ecs-engine/core/component_setting.h"
#include "ecs-engine/utility/rtti/class_index.h"
#include "ecs-engine/utility/tmp/type_mapping.h"

namespace ecs {

template <typename ComponentSetting, typename ThreadingModel>
class ComponentManagementPolicy {
 public:
  template <typename T>
  using ComponentManager = ComponentManager<T, ThreadingModel>;

  class Builder;

  template <typename T>
  const ComponentManager<T>& GetComponentManager(
      tmp::Type2Type<T>) const noexcept;
  template <typename T>
  ComponentManager<T>& GetComponentManager(tmp::Type2Type<T>) noexcept;

  template <typename T>
  const T& GetSingletonComponent() const noexcept;
  template <typename T>
  T& GetSingletonComponent() noexcept;

 private:
  using ManagerList =
      typename tmp::ListWrapperOf<ComponentManager,
                                  typename ComponentSetting::Components>::Type;

  using SingletonComponentList = typename ComponentSetting::SingletonComponents;

  using ManagerPtrTuple =
      typename tmp::TupleWrapperOf<std::unique_ptr, ManagerList>::Type;
  using SingletonCompPtrTuple =
      typename tmp::TupleWrapperOf<std::unique_ptr,
                                   SingletonComponentList>::Type;

  ManagerPtrTuple manager_ptr_tup_;
  SingletonCompPtrTuple singleton_comp_tup_;
};

template <typename ComponentSetting, typename ThreadingModel>
class ComponentManagementPolicy<ComponentSetting, ThreadingModel>::Builder {
 public:
  template <typename T, typename... Args>
  ComponentManager<T>& MakeComponentManager(Args&&... args);

  template <typename T, typename... Args>
  T& MakeSingletonComponent(Args&&... args);

  ComponentManagementPolicy Build();

 private:
  ComponentManagementPolicy::ManagerPtrTuple manager_ptr_tup_;
  ComponentManagementPolicy::SingletonCompPtrTuple singleton_comp_tup_;
};

//////////////////////////////////////////////////////////////////////////

template <typename ComponentSetting, typename ThreadingModel>
template <typename T>
inline const typename ComponentManagementPolicy<
    ComponentSetting, ThreadingModel>::template ComponentManager<T>&
ComponentManagementPolicy<ComponentSetting, ThreadingModel>::
    GetComponentManager(tmp::Type2Type<T>) const noexcept {
  return *std::get<std::unique_ptr<ComponentManager<T>>>(manager_ptr_tup_);
}

template <typename ComponentSetting, typename ThreadingModel>
template <typename T>
inline typename ComponentManagementPolicy<
    ComponentSetting, ThreadingModel>::template ComponentManager<T>&
ComponentManagementPolicy<ComponentSetting, ThreadingModel>::
    GetComponentManager(tmp::Type2Type<T>) noexcept {
  return const_cast<ComponentManager<T>&>(
      static_cast<const ComponentManagementPolicy&>(*this)
          .GetComponentManager<T>());
}

template <typename ComponentSetting, typename ThreadingModel>
template <typename T>
inline const T& ComponentManagementPolicy<
    ComponentSetting, ThreadingModel>::GetSingletonComponent() const noexcept {
  return *std::get<std::unique_ptr<T>>(singleton_comp_tup_);
}

template <typename ComponentSetting, typename ThreadingModel>
template <typename T>
inline T& ComponentManagementPolicy<
    ComponentSetting, ThreadingModel>::GetSingletonComponent() noexcept {
  return const_cast<T&>(static_cast<const ComponentManagementPolicy&>(*this)
                            .GetSingletonComponent<T>());
}

template <typename ComponentSetting, typename ThreadingModel>
template <typename T, typename... Args>
inline typename ComponentManagementPolicy<ComponentSetting,
                                          ThreadingModel>::ComponentManager<T>&
ComponentManagementPolicy<ComponentSetting, ThreadingModel>::Builder::
    MakeComponentManager(Args&&... args) {
  auto mgr = std::make_unique<ComponentManager<T>>(std::forward<Args>(args)...);
  auto& ref = *mgr;
  std::get<std::unique_ptr<ComponentManager<T>>>(manager_ptr_tup_) =
      std::move(mgr);
  return ref;
}

template <typename ComponentSetting, typename ThreadingModel>
template <typename T, typename... Args>
inline T& ComponentManagementPolicy<ComponentSetting, ThreadingModel>::Builder::
    MakeSingletonComponent(Args&&... args) {
  auto singleton_comp = std::make_unique<T>(std::forward<Args>(args)...);
  auto& ref = *singleton_comp;
  std::get<std::unique_ptr<T>>(singleton_comp_tup_) = std::move(singleton_comp);
  return ref;
}

namespace component_manager_policy_internal {

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

template <typename T>
typename std::enable_if<std::is_default_constructible<T>::value>::type
Construct(std::unique_ptr<T>& ptr) {
  ptr = std::make_unique<T>();
}

template <typename T>
typename std::enable_if<!std::is_default_constructible<T>::value>::type
Construct(std::unique_ptr<T>&) {
  assert(false &&
         "Failed to build singleton component. Please make non default "
         "constructible singleton component.");
}

}  // namespace component_manager_policy_internal

template <typename ComponentSetting, typename ThreadingModel>
inline ComponentManagementPolicy<ComponentSetting, ThreadingModel>
ComponentManagementPolicy<ComponentSetting, ThreadingModel>::Builder::Build() {
  assert(
      !component_manager_policy_internal::PtrTupleHasNull(manager_ptr_tup_) &&
      "Failed to build component manager policy. Component manager not set.");

  auto policy = ComponentManagementPolicy{};
  policy.manager_ptr_tup_ = std::move(manager_ptr_tup_);

  ecs::algo::StaticFor<std::tuple_size<SingletonCompPtrTuple>::value>(
      [&](auto i) {
        auto&& e = std::get<i>(singleton_comp_tup_);
        if (!e) {
          component_manager_policy_internal::Construct(e);
        }
      });
  policy.singleton_comp_tup_ = std::move(singleton_comp_tup_);
  return policy;
}

}  // namespace ecs