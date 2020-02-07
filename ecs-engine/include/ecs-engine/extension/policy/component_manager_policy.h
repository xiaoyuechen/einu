#ifndef COMPONENT_MANAGER_POLICY_H_
#define COMPONENT_MANAGER_POLICY_H_

#include "ecs-engine/core/component_manager.h"
#include "ecs-engine/core/component_setting.h"
#include "ecs-engine/utility/type_mapping.h"

namespace ecs {

namespace detail {
template <typename ComponentSetting, typename ThreadingModel>
struct TupleRefComponentManagerOf;
}  // namespace detail

template <typename ComponentSetting, typename SingletonComponentList,
          typename ThreadingModel>
class ComponentManagerPolicy {
 public:
  template <typename T>
  using ComponentManager = ComponentManager<T, ThreadingModel>;

  using TupleRefComponentManager =
      typename detail::TupleRefComponentManagerOf<ComponentSetting,
                                                  ThreadingModel>::Type;
  using TupleRefSingletonComponent =
      typename TupleRefOf<SingletonComponentList>::Type;

  ComponentManagerPolicy(TupleRefComponentManager manager_tup,
                         TupleRefSingletonComponent singleton_comp_tup);

  template <typename T>
  const ComponentManager<T>& GetComponentManager(Type2Type<T>) const noexcept;
  template <typename T>
  ComponentManager<T>& GetComponentManager(Type2Type<T>) noexcept;

  template <typename T>
  const T& GetSingletonComponent() const noexcept;
  template <typename T>
  T& GetSingletonComponent() noexcept;

 private:
  TupleRefComponentManager component_manager_tup_;
  TupleRefSingletonComponent singleton_component_tup_;
};

//////////////////////////////////////////////////////////////////////////

namespace detail {
template <typename ThreadingModel, typename... Ts>
struct TupleRefComponentManagerOf<ComponentSetting<ComponentList<Ts...>>,
                                  ThreadingModel> {
  using Type = std::tuple<ComponentManager<Ts, ThreadingModel>&...>;
};
}  // namespace detail

template <typename ComponentSetting, typename SingletonComponentList,
          typename ThreadingModel>
inline ComponentManagerPolicy<ComponentSetting, SingletonComponentList,
                              ThreadingModel>::
    ComponentManagerPolicy(TupleRefComponentManager manager_tup,
                           TupleRefSingletonComponent singleton_comp_tup)
    : component_manager_tup_(manager_tup)
    , singleton_component_tup_(singleton_comp_tup) {}

template <typename ComponentSetting, typename SingletonComponentList,
          typename ThreadingModel>
template <typename T>
inline const typename ComponentManagerPolicy<
    ComponentSetting, SingletonComponentList,
    ThreadingModel>::template ComponentManager<T>&
ComponentManagerPolicy<ComponentSetting, SingletonComponentList,
                       ThreadingModel>::GetComponentManager(Type2Type<T>) const
    noexcept {
  return std::get<ComponentManager<T>&>(component_manager_tup_);
}

template <typename ComponentSetting, typename SingletonComponentList,
          typename ThreadingModel>
template <typename T>
inline typename ComponentManagerPolicy<
    ComponentSetting, SingletonComponentList,
    ThreadingModel>::template ComponentManager<T>&
ComponentManagerPolicy<
    ComponentSetting, SingletonComponentList,
    ThreadingModel>::GetComponentManager(Type2Type<T>) noexcept {
  return const_cast<ComponentManager<T>&>(
      static_cast<const ComponentManagerPolicy&>(*this)
          .GetComponentManager<T>());
}

template <typename ComponentSetting, typename SingletonComponentList,
          typename ThreadingModel>
template <typename T>
inline const T& ComponentManagerPolicy<ComponentSetting, SingletonComponentList,
                                       ThreadingModel>::GetSingletonComponent()
    const noexcept {
  return std::get<T&>(singleton_component_tup_);
}

template <typename ComponentSetting, typename SingletonComponentList,
          typename ThreadingModel>
template <typename T>
inline T&
ComponentManagerPolicy<ComponentSetting, SingletonComponentList,
                       ThreadingModel>::GetSingletonComponent() noexcept {
  return std::get<T&>(singleton_component_tup_);
}

}  // namespace ecs

#endif  // COMPONENT_MANAGER_POLICY_H_
