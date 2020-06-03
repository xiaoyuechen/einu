#pragma once

#include "ecs-engine/utility/rtti/class_index.h"

namespace ecs {
namespace rtti {

class ClassIndexRegister {
 public:
  template <typename T>
  void Register() noexcept {
    auto& idx = GetClassIndex<T>();
    if (!IsAssigned(idx)) {
      idx = ++latest_idx_;
    }
  }

 private:
  rtti::ClassIndex latest_idx_{};
};

//template <typename... Ts>
//void RegisterMultiple(ClassIndexRegister& reg) {
//  (reg.Register<Ts>(), ...);
//}
//
//template <typename... Ts>
//void RegisterTypeList(ClassIndexRegister& reg, tmp::TypeList<Ts...>) {
//  RegisterMultiple<Ts...>(reg);
//}

}  // namespace rtti
}  // namespace ecs
