#pragma once

namespace einu {

class DefaultUnitPolicy {
 public:
  static constexpr float PixelPerUnit();

 private:
  static constexpr float kPixPerUnit = 1;
};

//////////////////////////////////////////////////////////////////////////

constexpr float einu::DefaultUnitPolicy::PixelPerUnit() { return kPixPerUnit; }

}  // namespace einu