#ifndef DEFAULT_UNIT_POLICY_H_
#define DEFAULT_UNIT_POLICY_H_

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

#endif  // DEFAULT_UNIT_POLICY_H_
