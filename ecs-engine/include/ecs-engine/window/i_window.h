#pragma once

namespace ecs {
namespace window {

class ITimeManager {
 public:
  virtual double GetTimeSeconds() = 0;
  virtual void SetTimeSeconds(double time) = 0;
};

class IClearer {
  virtual void Clear() = 0;
};

class IUpdater {
  virtual void Update() = 0;
};

class IInputRegister {
  virtual void 
};

class IWindow {
};

}  // namespace window
}  // namespace ecs
