#ifndef RECT_H_
#define RECT_H_

#include "ecs-engine/math/glm.h"

namespace ecs {

template <typename T>
struct Rect {
  T left = 0, top = 0, width = 0, height = 0;
};

template <typename T>
Rect<T> operator*(const glm::mat4& transform, const Rect<T>& rhs);

using IntRect = Rect<int>;

//////////////////////////////////////////////////////////////////////////

template <typename T>
Rect<T> operator*(const glm::mat4& transform, const Rect<T>& rhs) {
  auto top_left = glm::vec2(rhs.left, rhs.top);
  auto button_right = top_left + glm::vec2(rhs.width, rhs.height);
  //top_left *= transform;
  return Rect<T>{};

}

}  // namespace ecs

#endif  // RECT_H_
