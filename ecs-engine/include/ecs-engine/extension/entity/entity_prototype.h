#pragma once

#include <memory>
#include <tuple>

#include "ecs-engine/core/component_list.h"
#include "ecs-engine/core/component.h"
#include "ecs-engine/utility/algorithm.h"
#include "ecs-engine/utility/tmp/type_list.h"
#include "ecs-engine/utility/tmp/type_mapping.h"

namespace ecs {

template <typename ComponentList>
class EntityPrototype {
  using CompPtrTup =
      typename tmp::TupleWrapperOf<std::unique_ptr,
                                   typename ComponentList::TypeList>::Type;

 public:
  template <typename T>
  T& AddComponent();
  template <typename T>
  void RemoveComponent();
  template <typename T>
  T& GetComponent();
  template <typename T>
  const T& GetComponent() const;

  template <typename EntityManager>
  typename EntityManager::EntityHandle CloneEntity(
      EntityManager& ett_mgr) const;

 private:
  template <typename T>
  std::unique_ptr<T>& GetCompPtrRef();

  template <typename T>
  const std::unique_ptr<T>& GetCompPtrRef() const;

  CompPtrTup tup_;
};

//////////////////////////////////////////////////////////////////////////

template <typename ComponentList>
template <typename T>
inline T& EntityPrototype<ComponentList>::AddComponent() {
  auto& ptr = GetCompPtrRef<T>();
  ptr = std::make_unique<T>();
  return *ptr;
}

template <typename ComponentList>
template <typename T>
inline void EntityPrototype<ComponentList>::RemoveComponent() {
  auto& ptr = GetCompPtrRef();
  ptr.reset();
}

template <typename ComponentList>
template <typename T>
inline T& EntityPrototype<ComponentList>::GetComponent() {
  return const_cast<T&>(
      static_cast<const EntityPrototype&>(*this).GetComponent<T>());
}

template <typename ComponentList>
template <typename T>
inline const T& EntityPrototype<ComponentList>::GetComponent() const {
  return *GetCompPtrRef();
}

template <typename ComponentList>
template <typename EntityManager>
inline typename EntityManager::EntityHandle
EntityPrototype<ComponentList>::CloneEntity(EntityManager& ett_mgr) const {
  auto ett_handle = ett_mgr.CreateEntity();
  algo::StaticFor<tmp::Size<typename ComponentList::TypeList>::value>([&](auto i) {
    auto& ptr = std::get<i>(tup_);
    if (ptr) {
      auto& comp =
          ett_handle
              .AddComponent<std::remove_reference<decltype(*ptr)>::type>();
      comp = *ptr;
    }
  });
  return ett_handle;
}

template <typename ComponentList>
template <typename T>
inline const std::unique_ptr<T>& EntityPrototype<ComponentList>::GetCompPtrRef()
    const {
  return std::get<std::unique_ptr<T>>(tup_);
}

template <typename ComponentList>
template <typename T>
inline std::unique_ptr<T>& EntityPrototype<ComponentList>::GetCompPtrRef() {
  return const_cast<std::unique_ptr<T>&>(
      static_cast<const EntityPrototype&>(*this).GetCompPtrRef<T>());
}

}  // namespace ecs
