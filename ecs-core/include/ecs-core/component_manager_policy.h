#ifndef COMPONENT_MANAGER_POLICY_H_
#define COMPONENT_MANAGER_POLICY_H_

#include "ecs-core/component_manager.h"
#include "ecs-core/component_setting.h"
#include "ecs-core/utility/type_mapping.h"

namespace ecs {

namespace detail {
template <typename ComponentSetting, typename ThreadingModel>
struct TupleRefComponentManagerOf;
}  // namespace detail

template <typename ComponentSetting, typename ThreadingModel>
class ComponentManagerPolicy {
 public:
  template <typename T>
  using ComponentManager = ComponentManager<T, ThreadingModel>;

  template <typename... ComponentManagers>
  ComponentManagerPolicy(ComponentManagers&... comp_mgrs);

  template <typename T>
  const ComponentManager<T>& GetComponentManager(Type2Type<T>) const noexcept;
  template <typename T>
  ComponentManager<T>& GetComponentManager(Type2Type<T>) noexcept;

 private:
  using TupleRefComponentManager =
      typename detail::TupleRefComponentManagerOf<ComponentSetting,
                                                  ThreadingModel>::Type;

  TupleRefComponentManager t_ref_comp_mgr_;
};

//////////////////////////////////////////////////////////////////////////

namespace detail {
template <typename ThreadingModel, typename... Ts>
struct TupleRefComponentManagerOf<ComponentSetting<ComponentList<Ts...>>,
                                  ThreadingModel> {
  using Type = std::tuple<ComponentManager<Ts, ThreadingModel>&...>;
};
}  // namespace detail

template <typename ComponentSetting, typename ThreadingModel>
template <typename... ComponentManagers>
inline ComponentManagerPolicy<ComponentSetting, ThreadingModel>::
    ComponentManagerPolicy(ComponentManagers&... comp_mgrs)
    : t_ref_comp_mgr_(comp_mgrs...) {}

template <typename ComponentSetting, typename ThreadingModel>
template <typename T>
inline const typename ComponentManagerPolicy<
    ComponentSetting,
    ThreadingModel>::template ComponentManager<T>&
ComponentManagerPolicy<ComponentSetting, ThreadingModel>::GetComponentManager(
    Type2Type<T>) const noexcept {
  return std::get<ComponentManager<T>&>(t_ref_comp_mgr_);
}

template <typename ComponentSetting, typename ThreadingModel>
template <typename T>
inline typename ComponentManagerPolicy<
    ComponentSetting,
    ThreadingModel>::template ComponentManager<T>&
ComponentManagerPolicy<ComponentSetting, ThreadingModel>::GetComponentManager(
    Type2Type<T>) noexcept {
  return const_cast<ComponentManager<T>&>(
      static_cast<const ComponentManagerPolicy&>(*this)
          .GetComponentManager<T>());
}

}  // namespace ecs

#endif  // COMPONENT_MANAGER_POLICY_H_
