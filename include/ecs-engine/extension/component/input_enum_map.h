#pragma once

#include <array>
#include <tuple>

#include "einu-engine/core/i_singleton_component.h"
#include "einu-engine/input/input_def.h"

namespace einu {
namespace comp {
namespace single {
class InputEnumMap : public ISingletonComponent {
 public:


 private:
  template <typename T>
  using Map = std::array<T, GetCount<T>()>;

  template <typename T>
  const Map<T>& GetMap() const noexcept {
    return std::get<Map<T>>(maps_);
  }

  template <typename T>
  Map<T>& GetMap() noexcept {
    return std::get<Map<T>>(maps_);
  }

  std::tuple<Map<MouseButton>, Map<KeyboardKey>,
             Map<ModifierKeyFlag>>
      maps_;
};
}  // namespace single
}  // namespace comp
}  // namespace einu
