#pragma once

namespace ecs {

class DefaultUnitPolicy {
 public:
  static constexpr float PixelPerUnit();

 private:
  static constexpr float kPixPerUnit = 1;
};

//////////////////////////////////////////////////////////////////////////

constexpr float ecs::DefaultUnitPolicy::PixelPerUnit() { return kPixPerUnit; }

}  // namespace ecs