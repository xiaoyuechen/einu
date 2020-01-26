#pragma once
#include "ecs-core/component/type_mask.h"
#include "ecs-core/entity_id.h"
#include "ecs-core/utility/pattern.h"
#include <map>

namespace ecs {
class Component_mask_manager {
 public:
  struct Subject;

 private:
  using mask_map = std::map<EntityID, TypeMask>;
  using subject_map = std::map<Component_type, Subject>;

 public:
  template <typename T>
  void add(const EntityID& e);
  template <typename T>
  void remove(const EntityID& e);
  const TypeMask& get(const EntityID& e) const;

  template <typename... Args>
  bool has_components(const EntityID& e) const;

  bool has_components(const EntityID& e, const TypeMask& m) const;

  template <typename T>
  patt::I_subject& get_subject();

 private:
  mask_map mask_map_;
  subject_map sbj_map_;
};

struct Component_mask_manager::Subject : public patt::I_subject {
  enum class Action { ADD, REMOVE } action;
  EntityID entity;
};
}  // namespace ecs

namespace ecs {
template <typename T>
inline void Component_mask_manager::add(const EntityID& e) {
  auto type = type_of<T>();
  mask_map_[e].set(type);

  auto& sbj = sbj_map_[type];
  sbj.action = Component_mask_manager::Subject::Action::ADD;
  sbj.entity = e;
  sbj.broadcast();
}

template <typename T>
inline void Component_mask_manager::remove(const EntityID& e) {
  auto type = type_of<T>();
  mask_map_[e].reset(type);

  auto& sbj = sbj_map_[type];
  sbj.action = Component_mask_manager::Subject::Action::ADD;
  sbj.entity = e;
  sbj.broadcast();
}

inline const TypeMask& Component_mask_manager::get(
    const EntityID& e) const {
  return mask_map_.at(e);
}

template <typename... Args>
inline bool Component_mask_manager::has_components(const EntityID& e) const {
  auto m = TypeMask{type_of<Args>()...};
  return has_components(e, m);
}

inline bool Component_mask_manager::has_components(const EntityID& e,
                                            const TypeMask& m) const {
  return (m & mask_map_.at(e)) == m;
}

template <typename T>
inline patt::I_subject& Component_mask_manager::get_subject() {
  return sbj_map_[type_of<T>()];
}
}  // namespace ecs