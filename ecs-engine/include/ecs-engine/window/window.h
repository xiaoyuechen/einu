#ifndef WINDOW_H_
#define WINDOW_H_

#include <tuple>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "ecs-engine/input/input.h"
#include "ecs-engine/input/input_fn.h"
#include "ecs-engine/math/glm.h"
#include "ecs-engine/utility/type_mapping.h"

namespace ecs {

class Window {
 public:
  enum class Mode {
    WINDOWED,
    FULLSCREEN,
  };

  Window(Mode mode, int width, int height, const char* title);
  ~Window();

  template <typename Fn>
  const Fn& GetInputCallback() const;
  template <typename Fn>
  void SetInputCallback(const Fn& callback);

  void SetWindowShouldClose(bool should_close = true);
  bool ShouldClose() const;
  void SwapBuffer();
  void PollEvents();

 private:
  void SetInputCallback(Type2Type<input::KeyFn>, GLFWkeyfun callback);
  void SetInputCallback(Type2Type<input::MouseButtonFn>,
                        GLFWmousebuttonfun callback);
  void SetInputCallback(Type2Type<input::ScrollFn>, GLFWscrollfun callback);
  void SetInputCallback(Type2Type<input::CursorPosFn>,
                        GLFWcursorposfun callback);

  GLFWwindow& window_;

  std::tuple<input::KeyFn,
             input::MouseButtonFn,
             input::ScrollFn,
             input::CursorPosFn>
      input_callback_tuple_;
};

//////////////////////////////////////////////////////////////////////////

template <typename Fn>
inline const Fn& Window::GetInputCallback() const {
  return std::get<Fn>(input_callback_tuple_);
}

template <typename Fn>
inline void Window::SetInputCallback(const Fn& callback) {
  const Fn& fn = GetInputCallback<Fn>();
  const_cast<Fn&>(fn) = callback;
  SetInputCallback(Type2Type<Fn>{}, &Fn::Invoke);
}

}  // namespace ecs

#endif  // WINDOW_H_
