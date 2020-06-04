#pragma once

#include "ecs-engine/core/i_component.h"
#include "ecs-engine/core/i_singleton_component.h"
#include "ecs-engine/utility/rtti/class_index_register.h"
#include "ecs-engine/utility/tmp/type_list.h"

namespace ecs {

template <typename... Ts>
using ComponentList = tmp::SubtypeList<IComponent, Ts...>;
template <typename... Ts>
using SingletonComponentList = tmp::SubtypeList<ISingletonComponent, Ts...>;

namespace component_context_internal {
template <typename... Ts>
void RegisterTypeList(rtti::ClassIndexRegister& reg, tmp::TypeList<Ts...>) {
  (reg.Register<Ts>(rtti::ClassIndex(tmp::IndexOf<TypeList, Ts>::value)), ...);
}

template <typename ComponentList>
struct ComponentMask {
  using Type = std::bitset<tmp::Size<ComponentList>::value>;
};
}  // namespace component_context_internal

template <typename ComponentList, typename SingletonComponentList>
class ComponentContext {
 public:
  enum class Type {
    kComponent,
    kSingletonComponent,
  };

  using ComponentMask =
      component_context_internal::ComponentMask<ComponentList>::Type;
  using size_type = rtti::ClassIndexRegister::size_type;

  ComponentContext() {
    component_context_internal::RegisterTypeList<ComponentList>(
        regs_[Type.kComponent]);
    component_context_internal::RegisterTypeList<SingletonComponentList>(
        regs_[Type.kSingletonComponent]);
  }

  size_type GetComponentTypeCount(Type type) const noexcept {
    return regs_[type].GetRegisteredCount();
  }

 private:
  std::map<Type, rtti::ClassIndexRegister> regs_;
};

}  // namespace ecs