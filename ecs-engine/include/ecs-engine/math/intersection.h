#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include <array>

#include "ecs-engine/math/glm.h"
#include "ecs-engine/math/primitive.h"

namespace ecs {

class LineLineIntersectTest {
 public:
  constexpr LineLineIntersectTest(const LineSegment2D& l1,
                                  const LineSegment2D& l2);

  constexpr bool IsParallel() const;
  constexpr bool IsIntersectionOnFirstSeg() const;
  constexpr bool IsIntersectionOnSecondSeg() const;
  constexpr glm::vec2 GetIntersectionPoint() const;

 private:
  constexpr float GetT() const noexcept;
  constexpr float GetU() const noexcept;

  float x1_, x2_, x3_, x4_;
  float y1_, y2_, y3_, y4_;
  float denominator_;
};

//constexpr std::array<glm::vec2, 2> RectLineIntersect(
//    const FloatRect& rect, const LineSegment2D& line) {
//  /** World Rect
//   * A  ------ D
//   *   |      |
//   * B  ------ C
//   */
//  auto a = glm::vec2{rect.left, rect.top};
//  auto b = a + 
//  constexpr std::array<glm::vec2, 4> verts = {
//      glm::vec2{rect.left, rect.top},  // A
//      glm::vec2{0, 0},                  // B
//      glm::vec2{kWorldDimension.x, 0},  // C
//      kWorldDimension,                  // D
//  };
//
//  std::array<glm::vec2, 2> intersects{glm::vec2{-666, -666},
//                                      glm::vec2{-666, -666}};
//  std::size_t intersect_count = 0;
//  for (std::size_t i = 0; i != 4; ++i) {
//    const auto &v_1 = verts[i], v_2 = verts[(i + 1) % 4];
//    auto side = ecs::linalg::LineSegment2D{v_1, v_2};
//    auto intersection_test = ecs::linalg::LineIntersectionTest{line, side};
//    if (!intersection_test.IsParallel() &&
//        intersection_test.IsIntersectionOnSecondSeg()) {
//      auto intersection = intersection_test.GetIntersectionPoint();
//      if (std::find(intersects.begin(), intersects.end(), intersection) ==
//          intersects.end()) {
//#pragma warning(suppress : 28020)
//        intersects[intersect_count++] = intersection;
//      }
//    }
//  }
//  return intersects;
//}

//////////////////////////////////////////////////////////////////////////

inline constexpr LineLineIntersectTest::LineLineIntersectTest(
    const LineSegment2D& l1, const LineSegment2D& l2)
    // reference: https://en.wikipedia.org/wiki/Line-line_intersection
    : x1_(l1.start.x)
    , x2_(l1.end.x)
    , x3_(l2.start.x)
    , x4_(l2.end.x)
    , y1_(l1.start.y)
    , y2_(l1.end.y)
    , y3_(l2.start.y)
    , y4_(l2.end.y)
    , denominator_((x1_ - x2_) * (y3_ - y4_) - (y1_ - y2_) * (x3_ - x4_)) {}

inline constexpr bool LineLineIntersectTest::IsParallel() const {
  return denominator_ == 0;
}

inline constexpr bool LineLineIntersectTest::IsIntersectionOnFirstSeg() const {
  auto t = GetT();
  return 0 <= t && t <= 1;
}

inline constexpr bool LineLineIntersectTest::IsIntersectionOnSecondSeg() const {
  auto u = GetU();
  return 0 <= u && u <= 1;
}

inline constexpr glm::vec2 LineLineIntersectTest::GetIntersectionPoint() const {
  auto t = GetT();
  return glm::vec2(x1_ + t * (x2_ - x1_), y1_ + t * (y2_ - y1_));
}

inline constexpr float LineLineIntersectTest::GetT() const noexcept {
  return ((x1_ - x3_) * (y3_ - y4_) - (y1_ - y3_) * (x3_ - x4_)) / denominator_;
}

inline constexpr float LineLineIntersectTest::GetU() const noexcept {
  return -((x1_ - x2_) * (y1_ - y3_) - (y1_ - y2_) * (x1_ - x3_)) /
         denominator_;
}

}  // namespace ecs

#endif  // INTERSECTION_H_
