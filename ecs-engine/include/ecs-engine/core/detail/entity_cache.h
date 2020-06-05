#pragma once

#include <functional>

#include "ecs-engine/core/entity.h"
#include "ecs-engine/core/entity_id.h"
#include "ecs-engine/utility/rtti/class_index.h"

namespace ecs {
namespace detail {

template <typename ThreadingModel>
class EntityCache : public ThreadingModel {
 public:
  struct ComponentsEids {
    std::vector<IComponent*> comps;
    std::vector<EntityID> eids;

    void Clear() {
      comps.clear();
      eids.clear();
    }
  };

  template <typename... Ts>
  void SetTypes() {
    (comp_idx_vec_.push_back(rtti::GetClassIndex<Ts>()), ...);
  }

  void Register(Entity& ett) {
    id_ett_map_.insert({ett.GetEntityID(), ett});
    is_expired_ = true;
  }

  void Unregister(const Entity& ett) {
    id_ett_map_.erase(ett.GetEntityID());
    is_expired_ = true;
  }

  const ComponentsEids& Get() const {
    if (is_expired_) {
      typename ThreadingModel::Lock lock(const_cast<EntityCache&>(*this));
      Refresh();
    }
    return comps_eids_;
  }

 private:
  void Refresh() const {
    if (!is_expired_) return;

    comps_eids_.Clear();
    for (auto&& [eid, ett] : id_ett_map_) {
      comps_eids_.eids.emplace_back(eid);
      for (auto idx : comp_idx_vec_) {
        auto& comp = ett.GetComponent(idx);
        comps_eids_.comps.emplace_back(&comp);
      }
    }
    is_expired_ = false;
  }

  std::vector<rtti::ClassIndex> comp_idx_vec_;
  std::map<EntityID, Entity&> id_ett_map_;  // for fast entity unregister
  mutable ComponentsEids comps_eids_;       // for fast iteration
  mutable bool is_expired_ = false;         // to know when to refresh comps
};

}  // namespace detail
}  // namespace ecs