#ifndef GLM_H_
#define GLM_H_

#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable : ALL_CODE_ANALYSIS_WARNINGS 4201 4127)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#pragma warning(pop)

namespace ecs {

namespace math {
template <typename T>
glm::vec<3, T> GetPosition(const glm::mat<4, 4, T>& transform);

template <typename T>
void SetPosition(glm::mat<4, 4, T>& transform, const glm::vec<3, T>& position);

template <typename T>
glm::vec<3, T> GetScale(const glm::mat<4, 4, T>& transform);

template <typename T>
void SetScale(glm::mat<4, 4, T>& transform, const glm::vec<3, T>& scale);

//////////////////////////////////////////////////////////////////////////

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
  return glm::vec<3, T>{transform[0][0], transform[1][1], transform[2][2]};
}

template <typename T>
void SetScale(glm::mat<4, 4, T>& transform, const glm::vec<3, T>& scale) {
  for (int i = 0; i != 3; ++i) {
    transform[i][i] = scale[i];
  }
}



}  // namespace math
}  // namespace ecs

#endif  // GLM_H_
