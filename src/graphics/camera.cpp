#include "einu-engine/graphics/camera.h"

namespace einu {

Camera::Camera(const glm::mat4& projection)
    : projection_(projection) {}

void Camera::SetProjection(const glm::mat4& projection) {
  projection_ = projection;
}

void Camera::Refresh() {
  glm::vec3 x(1.f, 0.f, 0.f);
  glm::vec3 y(0.f, 1.f, 0.f);
  glm::vec3 z(0.f, 0.f, 1.f);
  glm::mat4 ry = glm::rotate(glm::mat4(1.f), yaw_, y);
  x = ry * glm::vec4(x, 0.f);
  z = ry * glm::vec4(z, 0.f);
  glm::mat4 rx = glm::rotate(glm::mat4(1.f), pitch_, x);
  z = rx * glm::vec4(z, 0.f);
  y = rx * glm::vec4(y, 0.f);
  view_ = glm::mat4(1.f);
  view_[0][0] = x.x;
  view_[1][0] = x.y;
  view_[2][0] = x.z;
  view_[0][1] = y.x;
  view_[1][1] = y.y;
  view_[2][1] = y.z;
  view_[0][2] = z.x;
  view_[1][2] = z.y;
  view_[2][2] = z.z;
  view_[3][0] = -glm::dot(position_, x);
  view_[3][1] = -glm::dot(position_, y);
  view_[3][2] = -glm::dot(position_, z);
  x_axis_ = x;
  y_axis_ = y;
  z_axis_ = z;
}

void Camera::rotate_x(float amount) { pitch_ += amount; }

void Camera::rotate_y(float amount) { yaw_ += amount; }

void Camera::forward(float amount) { position_ += z_axis_ * amount; }

void Camera::sidestep(float amount) { position_ += x_axis_ * amount; }

void Camera::go_up(float amount) { position_ += y_axis_ * amount; }

glm::mat4 Camera::get_camera_matrix() const { return projection_ * view_; }

glm::mat4 Camera::get_view() const { return view_; }

glm::mat4 Camera::get_projection() const { return projection_; }

}  // namespace einu