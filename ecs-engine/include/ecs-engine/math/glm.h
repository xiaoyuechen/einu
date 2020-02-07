#ifndef GLM_H_
#define GLM_H_

#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable : ALL_CODE_ANALYSIS_WARNINGS 4201 4127)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#pragma warning(pop)
#include <tuple>

namespace ecs {

namespace math {

template <typename T>
struct Composition {
  glm::vec<3, T> scale;
  glm::tquat<T> rotation;
  glm::vec<3, T> translation;
  glm::vec<3, T> skew;
  glm::vec<4, T> perspective;
};

template <typename T>
Composition<T> GetComposition(const glm::mat<4, 4, T>& transform);

template <typename T>
glm::vec<3, T> GetPosition(const glm::mat<4, 4, T>& transform);
template <typename T>
void SetPosition(glm::mat<4, 4, T>& transform, const glm::vec<3, T>& position);

template <typename T>
glm::vec<3, T> GetScale(const glm::mat<4, 4, T>& transform);
template <typename T>
void SetScale(glm::mat<4, 4, T>& transform, const glm::vec<3, T>& scale);

template <typename T>
glm::tquat<T> GetRotation(const glm::mat<4, 4, T>& transform);
template <typename T>
void SetRotation(glm::mat<4, 4, T> & transform,
                  const glm::tquat<T>& rotation);

//////////////////////////////////////////////////////////////////////////

template <typename T>
Composition<T> GetComposition(const glm::mat<4, 4, T>& transform) {
  auto composition = Composition{};
  glm::decompose(composition.transform, composition.scale, composition.rotation,
                 composition.translation, composition.skew,
                 composition.perspective);
  return composition;
}

template <typename T>
glm::vec<3, T> GetPosition(const glm::mat<4, 4, T>& transform) {
  return glm::vec<3, T>(transform[3]);
}

template <typename T>
void SetPosition(glm::mat<4, 4, T>& transform, const glm::vec<3, T>& position) {
  memcpy(&transform[3], &position[0], 3 * sizeof(T));
}

template <typename T>
glm::vec<3, T> GetScale(const glm::mat<4, 4, T>& transform) {
  auto composition = GetComposition(transform);
  return composition.scale;
}

template <typename T>
void SetScale(glm::mat<4, 4, T>& transform, const glm::vec<3, T>& scale) {
  auto composition = GetComposition(transform);
  transform = composition.translation * composition.rotation * scale;
}

template <typename T>
glm::tquat<T> GetRotation(const glm::mat<4, 4, T>& transform) {
  auto composition = GetComposition(transform);
  return glm::conjugate(composition.rotation);
}

template <typename T>
void SetRotation(glm::mat<4, 4, T> & transform,
                  const glm::tquat<T>& rotation) {
  auto composition = GetComposition(transform);
  return composition.translation * glm::toMat4(rotation) * composition.scale;
}

}  // namespace math
}  // namespace ecs

#endif  // GLM_H_