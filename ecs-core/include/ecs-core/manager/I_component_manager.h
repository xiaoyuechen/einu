#pragma once
namespace ecs {
class I_component_manager {
 public:
  virtual ~I_component_manager();
};
}

namespace ecs {
inline I_component_manager::~I_component_manager() {}
}