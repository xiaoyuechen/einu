#pragma once

#include <map>
#include <utility>
#include <vector>

#include "ecs-engine/core/detail/component_mask.h"
#include "ecs-engine/core/detail/entity_cache.h"
#include "ecs-engine/core/entity.h"
#include "ecs-engine/core/entity_id.h"

namespace ecs {
namespace detail {

template <typename Tuple, typename Iter, size_t... Is>
auto MakeTuple(Iter iter, std::index_sequence<Is...>) {
  return std::forward_as_tuple(
      static_cast<typename std::tuple_element<Is, Tuple>::type>(
          **(iter + Is))...);
}

template <typename ThreadingModel>
class EntityCacheManager {
 public:
  using EntityCache = EntityCache<ThreadingModel>;

  template <typename... Ts>
  void RegisterInterest() {
    const auto& mask = GetComponentMaskStatic<Ts...>();
    auto [it, success] = cache_map_.emplace(
        std::piecewise_construct, std::make_tuple(&mask), std::make_tuple());
    if (success) {
      it->second.SetTypes<Ts...>();
    }
  }

  void RegisterEntity(Entity& ett) {
    for (auto&& [mask, cache] : cache_map_) {
      if ((*mask & ett.GetComponentMask()) == *mask) {
        cache.Register(ett);
      }
    }
  }

  void UnregisterEntity(const Entity& ett) {
    for (auto&& [mask, cache] : cache_map_) {
      if ((*mask & ett.GetComponentMask()) == *mask) {
        cache.Unregister(ett);
      }
    }
  }

  template <typename... Ts>
  void GetComponentsEids(std::vector<std::tuple<Ts&...>>* tuple_dest,
                         std::vector<EntityID>* eid_dest) const {
    const auto& mask = GetComponentMaskStatic<Ts...>();
    auto& cache = cache_map_.at(&mask);
    const auto& comps_eids = cache.Get();
    const auto& comps = comps_eids.comps;
    for (auto it = comps.begin(); it != comps.end(); it += sizeof...(Ts)) {
      auto tup = MakeTuple<std::tuple<Ts&...>>(
          it, std::make_index_sequence<sizeof...(Ts)>());
      tuple_dest->emplace_back(tup);
    }
    *eid_dest = comps_eids.eids;
  }

 private:
  using CacheMap = std::map<const ComponentMask*, EntityCache>;

  CacheMap cache_map_;
};

}  // namespace detail
}  // namespace ecs