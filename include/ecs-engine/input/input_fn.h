#pragma once

#include <functional>

#include "einu-engine/input/input.h"

namespace einu {
namespace input {

template <typename... FnArgs>
class InputFn {
 public:
  using Fn = std::function<void(FnArgs...)>;
  InputFn() = default;
  explicit InputFn(const Fn& fn)
      : fn_(fn) {}

 protected:
  Fn fn_;
};

using KeyFn = InputFn<KeyboardKey, Action, ModifierKey>;
using MouseButtonFn = InputFn<MouseButton, Action, ModifierKey>;
using ScrollFn = InputFn<double, double>;
using CursorPosFn = InputFn<double, double>;

}  // namespace input
}  // namespace einu
