#pragma once

#include <string>

namespace ecs {
namespace window {

class GLCreater {
 public:
  struct Hint {
    int major, minor;
  };

  enum class Mode {
    kWindowed,
    kFullScreen,
  };

  struct Setting {
    Mode mode = Mode::kWindowed;
    int width = 0, height = 0;
    std::string title{};
  };

  GLCreater(Hint hint, const Setting& setting)
      : hint_(hint)
      , setting_(setting) {}

  void* CreateWindow() const;

 private:
  Hint hint_;
  const Setting& setting_;
};

}  // namespace window
}  // namespace ecs