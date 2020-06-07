#pragma once

#include <functional>
#include <set>

#include "ecs-engine/core/entity_data.h"
#include "ecs-engine/core/entity_id.h"
#include "ecs-engine/utility/rtti/class_index.h"

namespace ecs {
namespace detail {

template <typename ThreadingModel>
class EntityCache : public ThreadingModel {
 public:
  struct CacheData {
    std::vector<IComponent*> comps;
    std::vector<EntityData*> etts;

    void Clear() {
      comps.clear();
      etts.clear();
    }
  };

  EntityCache(std::initializer_list<rtti::ClassIndex> l)
      : comp_idx_seq_(l) {}

  void Register(EntityData& ett) {
    etts_.insert(&ett);
    is_expired_ = true;
  }

  void Unregister(EntityData& ett) {
    etts_.erase(&ett);
    is_expired_ = true;
  }

  const CacheData& Get() const {
    if (is_expired_) {
      typename ThreadingModel::Lock lock(const_cast<EntityCache&>(*this));
      Refresh();
    }
    return cache_data_;
  }

 private:
  void Refresh() const {
    if (!is_expired_) return;

    cache_data_.Clear();
    for (auto ett : etts_) {
      cache_data_.etts.emplace_back(ett);
      for (auto idx : comp_idx_seq_) {
        auto& comp = ett->GetComponent(idx);
        cache_data_.comps.emplace_back(&comp);
      }
    }
    is_expired_ = false;
  }

  std::vector<rtti::ClassIndex> comp_idx_seq_;
  std::set<EntityData*> etts_;       // for fast entity unregister
  mutable CacheData cache_data_;     // for fast iteration
  mutable bool is_expired_ = false;  // to know when to refresh comps
};

}  // namespace detail
}  // namespace ecs