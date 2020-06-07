#pragma once

#include <map>
#include <utility>
#include <vector>

#include "ecs-engine/core/detail/component_mask.h"
#include "ecs-engine/core/detail/entity_cache.h"
#include "ecs-engine/core/entity_data.h"
#include "ecs-engine/utility/rtti/class_index.h"

namespace ecs {
namespace detail {

template <typename ThreadingModel>
class EntityCacheManager {
 public:
  using EntityCache = EntityCache<ThreadingModel>;
  using CacheData = typename EntityCache::CacheData;

  void RegisterInterest(const ComponentMask* mask,
                        std::initializer_list<rtti::ClassIndex> idx_seq) {
    cache_map_.emplace(std::piecewise_construct, std::make_tuple(mask),
                       std::make_tuple(idx_seq));
  }

  void AfterAddComponent(EntityData& ett) {
    for (auto&& [mask, cache] : cache_map_) {
      if ((*mask & ett.GetComponentMask()) == *mask) {
        cache.Register(ett);
      }
    }
  }

  void BeforeRemoveComponent(EntityData& ett) {
    for (auto&& [mask, cache] : cache_map_) {
      if ((*mask & ett.GetComponentMask()) == *mask) {
        cache.Unregister(ett);
      }
    }
  }

  const CacheData& GetCacheData(const ComponentMask& mask) const {
    const auto& cache = cache_map_.at(&mask);
    return cache.Get();
  }

 private:
  using CacheMap = std::map<const ComponentMask*, EntityCache>;

  CacheMap cache_map_;
};

}  // namespace detail
}  // namespace ecs