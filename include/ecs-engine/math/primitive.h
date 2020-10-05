#pragma once

#include "einu-engine/math/glm.h"

namespace einu {

struct LineSegment2D {
  glm::vec2 start, end;
};

template <typename T>
struct Rect {
  T left = 0, buttom = 0, width = 0, height = 0;
};

template <typename T>
Rect<T> operator*(const glm::mat<4, 4, T>& transform, const Rect<T>& rhs);

using FloatRect = Rect<float>;
using IntRect = Rect<int>;

//////////////////////////////////////////////////////////////////////////

template <typename T>
Rect<T> operator*(const glm::mat<4, 4, T>& transform, const Rect<T>& rhs) {
  auto buttom_left = glm::vec3(rhs.left, rhs.buttom, 0);
  auto top_right = buttom_left + glm::vec3(rhs.width, rhs.height, 0);
  buttom_left *= transform;
  top_right *= transform;

  return Rect<T>{};
}

}  // namespace einu

