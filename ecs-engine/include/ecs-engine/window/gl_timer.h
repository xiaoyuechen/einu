#pragma once

namespace ecs {
namespace window {

class GLTimer {
 public:
  double GetTime() const;
  void SetTime(double time);
};

}  // namespace window
}  // namespace ecs