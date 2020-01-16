#pragma once
#include "ecs-core/admin/World.h"
#include "ecs-core/utility/pattern.h"
#include "ecs-core/utility/algorithm.h"

namespace ecs {
class I_system : public patt::I_observer {
 private:
  using time = float;
  using entity_chache = std::vector<Entity_id>;

 public:
  I_system(Entity_manager& entity_manager);
  virtual ~I_system();
  const Component_mask& get_component_mask() const;

  template <typename T>
  void add_required_component();

  virtual void update(time dt);

  virtual void observe(patt::I_subject& sbj) override;

 protected:
  Entity_manager& entity_manager_;
  entity_chache entity_chache_;

 private:
  Component_mask component_mask_;
};
}  // namespace ecs

namespace ecs {
inline I_system::I_system(Entity_manager& entity_manager)
    : entity_manager_(entity_manager) {}

inline I_system::~I_system() {}

inline const Component_mask& I_system::get_component_mask() const {
  return component_mask_;
}

inline void I_system::update([[maybe_unused]] time dt) {}

inline void I_system::observe(patt::I_subject& sbj) {
  const auto& s = static_cast<Component_mask_manager::Subject&>(sbj);
  auto action = s.action;
  auto e = s.entity;
  switch (action) {
    case ecs::Component_mask_manager::Subject::Action::ADD: {
      auto mask_manager = entity_manager_.get_component_mask_manager();
      if (mask_manager.has_components(e, component_mask_)) {
        entity_chache_.push_back(e);
      }
    } break;
    case ecs::Component_mask_manager::Subject::Action::REMOVE: {
      algo::erase_remove(entity_chache_, entity_chache_.begin(), entity_chache_.end(), e);
    } break;
  }
}

template <typename T>
inline void I_system::add_required_component() {
  component_mask_.set(type_of<T>());
  auto& comp_mask_manager = entity_manager_.get_component_mask_manager();
  auto& sbj = comp_mask_manager.get_subject<T>();
  subscribe(sbj);
}
}  // namespace ecs