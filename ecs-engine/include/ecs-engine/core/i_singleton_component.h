#pragma once

namespace ecs {

struct ISingletonComponent {
  virtual ~ISingletonComponent() = default;
};

}  // namespace ecs