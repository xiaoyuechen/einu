#pragma once
#include "einu-engine/math/glm.h"

namespace einu {

class Camera {
 public:
  Camera(const glm::mat4& projection);

  void SetProjection(const glm::mat4& projection);

  void Refresh();

  void rotate_x(float amount);
  void rotate_y(float amount);
  void forward(float amount);
  void sidestep(float amount);
  void go_up(float amount);

  glm::mat4 get_camera_matrix() const;
  glm::mat4 get_view() const;
  glm::mat4 get_projection() const;

 private:
  float yaw_ = 0;
  float pitch_ = 0;
  float roll_ = 0;

  glm::vec3 x_axis_ = glm::vec3(0.f);
  glm::vec3 y_axis_ = glm::vec3(0.f);
  glm::vec3 z_axis_ = glm::vec3(0.f);
  glm::vec3 position_ = glm::vec3(0.f);

  glm::mat4 projection_ = glm::mat4(1.f);
  glm::mat4 view_ = glm::mat4(1.f);
};

}  // namespace graphics