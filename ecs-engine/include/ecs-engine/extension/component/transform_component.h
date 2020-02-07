#ifndef TRANSFORM_COMPONENT_H_
#define TRANSFORM_COMPONENT_H_

#include "ecs-engine/core/component_tag.h"
#include "ecs-engine/math/glm.h"

namespace ecs {

class TransformComponent : public ComponentTag {
 public:
  const glm::vec3& GetPosition() const noexcept;
  const glm::quat& GetRotation() const noexcept;
  const glm::vec3& GetScale() const noexcept;
  const glm::mat4& GetTransform() const noexcept;

  void SetPosition(const glm::vec3& position);
  void SetRotation(const glm::quat& quat);
  void SetScale(const glm::vec3& scale);

 private:
  void UpdateTransformCache();
  void CopyPosition2Transform() noexcept;

  glm::vec3 position_{0, 0, 0};
  glm::quat rotation_{1, 0, 0, 0};
  glm::vec3 scale_{1, 1, 1};

  glm::mat4 transform_ = glm::mat4{1.f};  // cache
};

//////////////////////////////////////////////////////////////////////////

inline const glm::vec3& TransformComponent::GetPosition() const noexcept {
  return position_;
}

inline const glm::quat& TransformComponent::GetRotation() const noexcept {
  return rotation_;
}

inline const glm::vec3& TransformComponent::GetScale() const noexcept {
  return scale_;
}

inline const glm::mat4& TransformComponent::GetTransform() const noexcept {
  return transform_;
}

inline void TransformComponent::SetPosition(const glm::vec3& position) {
  position_ = position;
  CopyPosition2Transform();
}

inline void TransformComponent::SetRotation(const glm::quat& quat) {
  rotation_ = quat;
  transform_ = glm::toMat4(rotation_) * glm::scale(scale_);
  UpdateTransformCache();
}

inline void TransformComponent::SetScale(const glm::vec3& scale) {
  scale_ = scale;
  UpdateTransformCache();
}

inline void TransformComponent::UpdateTransformCache() {
  transform_ = glm::toMat4(rotation_) * glm::scale(scale_);
  memcpy(&transform_[3], &position_[0], sizeof(position_));
}

inline void TransformComponent::CopyPosition2Transform() noexcept {
  memcpy(&transform_[3], &position_[0], sizeof(position_));
}

// inline glm::mat4 GetTransformMatrix(const TransformComponent& transform) {
//  auto matrix = glm::mat4(1.f);
//  // matrix = glm::scale(transform.scale) * matrix;
//  // auto quat = glm::quat(glm::vec3(transform.rotation.roll,
//  // transform.rotation.pitch,
//  //                      transform.rotation.yaw));
//  // matrix = glm::toMat4(quat) * matrix;
//  matrix = glm::translate(transform.position_) * matrix;
//  return matrix;
//
//  // auto translation = glm::translate(transform.position);
//  // auto rotation = glm::rotate(transform.rotation.roll, glm::vec3(1, 0, 0))
//  *
//  //               glm::rotate(transform.rotation.pitch, glm::vec3(0, 1, 0)) *
//  //               glm::rotate(transform.rotation.yaw, glm::vec3(0, 0, 1));
//  // auto scale = glm::scale(transform.scale);
//  // return translation * rotation * scale;
//}

}  // namespace ecs

#endif  // TRANSFORM_COMPONENT_H_