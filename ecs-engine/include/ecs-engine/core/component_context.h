#pragma once

#include <map>

#include "ecs-engine/core/i_component.h"
#include "ecs-engine/core/i_singleton_component.h"
#include "ecs-engine/utility/rtti/class_index_register.h"
#include "ecs-engine/utility/tmp/type_list.h"

namespace ecs {

template <typename... Ts>
using ComponentList = tmp::SubtypeList<IComponent, Ts...>;
template <typename... Ts>
using SingletonComponentList = tmp::SubtypeList<ISingletonComponent, Ts...>;

namespace detail {
template <typename... Ts>
void RegisterTypeList(rtti::ClassIndexRegister& reg, tmp::TypeList<Ts...>) {
  (reg.Register<Ts>(
       rtti::ClassIndex(tmp::IndexOf<tmp::TypeList<Ts...>, Ts>::value)),
   ...);
}

}  // namespace detail

template <typename ComponentList, typename SingletonComponentList>
class ComponentContext {
 public:
  enum class Type {
    kComponent,
    kSingletonComponent,
  };

  using size_type = rtti::ClassIndexRegister::size_type;

  ComponentContext() {
    detail::RegisterTypeList(regs_[Type::kComponent], ComponentList{});
    detail::RegisterTypeList(regs_[Type::kSingletonComponent],
                             SingletonComponentList{});
  }

  size_type GetComponentTypeCount(Type type) const noexcept {
    return regs_[type].GetRegisteredCount();
  }

 private:
  std::map<Type, rtti::ClassIndexRegister> regs_;
};

}  // namespace ecs