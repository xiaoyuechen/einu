#pragma once

namespace ecs {

class Noncopyable {
 public:
  Noncopyable() = default;
  Noncopyable(const Noncopyable&) = delete;
  Noncopyable& operator=(const Noncopyable&) = delete;

 protected:
  ~Noncopyable() = default;
};
}  // namespace ecs