#pragma once

#include "einu-engine/math/glm.h"

namespace einu {

namespace transform_policy {
class UseCache {
 public:
  void UpdatePosition(const glm::vec3& position);
  // Decomposing matrix is slow (except for the position row),
  // so we pass in the the rotation and scale to recalculate the cache.
  void UpdateLinearTransform(const glm::quat& rot, const glm::vec3& scale);
  const glm::mat4& GetCachedTransform() const noexcept;

 private:
  glm::mat4 transform_ = glm::mat4{1.f};  // cache
};

class NoCache {
 public:
  static void UpdatePosition(const glm::vec3&) {}
  static void UpdateLinearTransform(const glm::quat&, const glm::vec3&) {}
};
}  // namespace transform_policy

template <typename CachePolicy>
class Transform : public CachePolicy {
 public:
  const glm::vec3& GetPosition() const noexcept;
  const glm::quat& GetRotation() const noexcept;
  const glm::vec3& GetScale() const noexcept;
  glm::mat4 GetTransform() const;

  void SetPosition(const glm::vec3& position);
  void SetRotation(const glm::quat& quat);
  void SetScale(const glm::vec3& scale);

 private:
  glm::vec3 position_{0, 0, 0};
  glm::quat rotation_{1, 0, 0, 0};
  glm::vec3 scale_{1, 1, 1};
};

//////////////////////////////////////////////////////////////////////////

namespace transform_policy {

inline void UseCache::UpdatePosition(const glm::vec3& position) {
  memcpy(&transform_[3], &position[0], sizeof(position));
}

inline void UseCache::UpdateLinearTransform(const glm::quat& rot,
                                            const glm::vec3& scale) {
  auto pos = glm::vec3{transform_[3]};
  transform_ = glm::toMat4(rot) * glm::scale(scale);
  UpdatePosition(pos);
}

inline const glm::mat4& transform_policy::UseCache::GetCachedTransform() const
    noexcept {
  return transform_;
}

}  // namespace transform_policy

template <typename CachePolicy>
inline const glm::vec3& Transform<CachePolicy>::GetPosition() const noexcept {
  return position_;
}

template <typename CachePolicy>
inline const glm::quat& Transform<CachePolicy>::GetRotation() const noexcept {
  return rotation_;
}

template <typename CachePolicy>
inline const glm::vec3& Transform<CachePolicy>::GetScale() const noexcept {
  return scale_;
}

template <typename CachePolicy>
inline glm::mat4 Transform<CachePolicy>::GetTransform() const {
  return glm::translate(position_) * glm::toMat4(rotation_) *
         glm::scale(scale_);
}

template <typename CachePolicy>
inline void Transform<CachePolicy>::SetPosition(const glm::vec3& position) {
  position_ = position;
  CachePolicy::UpdatePosition(position_);
}

template <typename CachePolicy>
inline void Transform<CachePolicy>::SetRotation(const glm::quat& quat) {
  rotation_ = quat;
  CachePolicy::UpdateLinearTransform(rotation_, scale_);
}

template <typename CachePolicy>
inline void Transform<CachePolicy>::SetScale(const glm::vec3& scale) {
  scale_ = scale;
  CachePolicy::UpdateLinearTransform(rotation_, scale_);
}

}  // namespace einu

