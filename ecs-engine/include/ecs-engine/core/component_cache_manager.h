#pragma once

#include <map>
#include <type_traits>
#include <vector>

#include "ecs-engine/core/component_array.h"
#include "ecs-engine/core/component_setting.h"
#include "ecs-engine/core/entity.h"
#include "ecs-engine/core/entity_id.h"

namespace ecs {

template <typename Entity>
class EntityCache {
 public:
  using Entities = std::vector<Entity&>;

  void Register(const Entity& ett) {
    id_ett_map.insert({ett.GetEntityID(), ett});
    is_expired = true;
  }

  void Unregister(const Entity& ett) {
    id_ett_map.erase(ett.GetEntityID());
    is_expired = true;
  }

  const Entities& Get() const {
    if (is_expired) {
      Refresh();
    }
    return etts;
  }

 private:
  void Refresh() const {
    etts.clear();
    for (auto&& [eid, ett] : id_ett_map) {
      etts.emplace_back(ett);
    }
    is_expired = false;
  }

  std::map<EntityID, const Entity&> id_ett_map;  // for fast entity unregister
  mutable Entities etts;                         // for fast iteration
  mutable bool is_expired = false;               // to know when to refresh etts
};

template <typename Entity, typename ThreadingModel>
class EntityCacheManager : public ThreadingModel {
 public:
  using ComponentMask = typename Entity::ComponentMask;
  using EntityCache = EntityCache<Entity>;
  using Entities = typename EntityCache::Entities;

  void RegisterComponentMask(const ComponentMask& mask) {
    cache_map_.insert(mask, Entities{});
  }

  void RegisterEntity(const Entity& ett) {
    typename ThreadingModel::Lock lock(*this);
    for (auto&& [mask, cache] : cache_map_) {
      if ((mask & ett.GetComponentMask()) == mask) {
        cache.Register(ett);
      }
    }
  }

  void UnregisterEntity(const Entity& ett) {
    typename ThreadingModel::Lock lock(*this);
    for (auto&& [mask, etts] : cache_map_) {
      if ((mask & ett.GetComponentMask()) == mask) {
        cache.Unregister(ett);
      }
    }
  }

  const Entities& GetEntities(const ComponentMask& mask) const {
    return cache_map_.at(mask);
  }

  Entities& GetEntities(const ComponentMask& mask) {
    return cache_map_.at(mask);
  }

 private:
  struct ComponentMaskCompare {
    bool operator()(const ComponentMask& lhs,
                    const ComponentMask& rhs) const noexcept {
      for (std::size_t i = 0; i != lhs.size(); ++i) {
        auto bit = lhs.size() - i - 1;
        if (lhs[bit] ^ rhs[bit]) return rhs[bit];
      }
      return false;
    }
  };

  using CacheMap =
      std::map<const ComponentMask&, EntityCache, ComponentMaskCompare>;
  CacheMap cache_map_;
};

template <typename ComponentSetting, typename ThreadingModel>
class ComponentCacheManager : public ThreadingModel {
 public:
  using ComponentMask = typename ComponentSetting::ComponentMask;
  using ComponentArray = ComponentArray<ComponentSetting>;

  struct CacheData {
    std::vector<EntityID> eid_arr;
    std::vector<ComponentArray> comp_arrs;
    void Clear() noexcept;
  };

  void RegisterComponentMask(const ComponentMask& mask);
  void AddEntity(const EntityID& eid, const ComponentMask& mask,
                 const ComponentArray& components);
  void RemoveEntity(const EntityID& eid, const ComponentMask& mask);

  const CacheData& GetCacheData(const ComponentMask& mask) const;
  CacheData& GetCacheData(const ComponentMask& mask);

 private:
  struct ComponentCache {
    std::map<EntityID, const ComponentArray&> ett_comp_map{};
    mutable bool is_expired = false;
    mutable CacheData cache_data{};
  };

  struct ComponentMaskCompare {
    bool operator()(const ComponentMask& lhs,
                    const ComponentMask& rhs) const noexcept;
  };

  std::map<ComponentMask, ComponentCache, ComponentMaskCompare> cache_map_{};
};

//////////////////////////////////////////////////////////////////////////

template <typename ComponentSetting, typename ThreadingModel>
inline void
ComponentCacheManager<ComponentSetting, ThreadingModel>::RegisterComponentMask(
    const ComponentMask& mask) {
  typename ThreadingModel::Lock lock(*this);
  cache_map_.insert({mask, ComponentCache{}});
}

template <typename ComponentSetting, typename ThreadingModel>
inline void ComponentCacheManager<ComponentSetting, ThreadingModel>::AddEntity(
    const EntityID& eid, const ComponentMask& mask,
    const ComponentArray& components) {
  typename ThreadingModel::Lock lock(*this);
  for (auto&& [required_mask, cache] : cache_map_) {
    if ((mask & required_mask) == required_mask) {
      cache.ett_comp_map.insert({eid, components});
      cache.is_expired = true;
    }
  }
}

template <typename ComponentSetting, typename ThreadingModel>
inline void
ComponentCacheManager<ComponentSetting, ThreadingModel>::RemoveEntity(
    const EntityID& eid, const ComponentMask& mask) {
  typename ThreadingModel::Lock lock(*this);
  for (auto&& [required_mask, cache] : cache_map_) {
    if ((mask & required_mask) == required_mask) {
      cache.ett_comp_map.erase(eid);
      cache.is_expired = true;
    }
  }
}

template <typename ComponentSetting, typename ThreadingModel>
const typename ComponentCacheManager<ComponentSetting,
                                     ThreadingModel>::CacheData&
ComponentCacheManager<ComponentSetting, ThreadingModel>::GetCacheData(
    const ComponentMask& mask) const {
  const auto& cache = cache_map_.at(mask);

  // refresh the cache data if expired
  if (cache.is_expired) {
    cache.cache_data.Clear();
    for (const auto& [eid, comp_arr] : cache.ett_comp_map) {
      cache.cache_data.eid_arr.push_back(eid);
      cache.cache_data.comp_arrs.push_back(comp_arr);
    }
    cache.is_expired = false;
  }
  return cache.cache_data;
}

template <typename ComponentSetting, typename ThreadingModel>
typename ComponentCacheManager<ComponentSetting, ThreadingModel>::CacheData&
ComponentCacheManager<ComponentSetting, ThreadingModel>::GetCacheData(
    const ComponentMask& mask) {
  return const_cast<CacheData&>(
      static_cast<const ComponentCacheManager&>(*this).GetCacheData(mask));
}

template <typename ComponentSetting, typename ThreadingModel>
inline bool ComponentCacheManager<ComponentSetting, ThreadingModel>::
    ComponentMaskCompare::operator()(const ComponentMask& lhs,
                                     const ComponentMask& rhs) const noexcept {
  /**
   * Comparators require strict weak orderings:
   * For all a, comp(a,a)==false
   * If comp(a,b)==true then comp(b,a)==false
   * if comp(a,b)==true and comp(b,c)==true then comp(a,c)==true
   */

  // TODO(Xiaoyue Chen): find out why the algorithm below doesn't work
  // auto bit_and = lhs & rhs;
  // if (bit_and == rhs) {
  //  if ((bit_and.flip() & lhs) != ComponentMask{}) {
  //    return true;
  //  }
  //}
  // return false;

  for (std::size_t i = 0; i != lhs.size(); ++i) {
    auto bit = lhs.size() - i - 1;
    if (lhs[bit] ^ rhs[bit]) return rhs[bit];
  }

  return false;
}

template <typename ComponentSetting, typename ThreadingModel>
inline void ComponentCacheManager<ComponentSetting,
                                  ThreadingModel>::CacheData::Clear() noexcept {
  eid_arr.clear();
  comp_arrs.clear();
}

}  // namespace ecs