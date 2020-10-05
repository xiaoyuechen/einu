#pragma once

#include <map>
#include <memory>

#include "einu-engine/core/component_pool.h"
#include "einu-engine/utility/rtti/class_index_storage.h"

namespace einu {

class ComponentPoolManager {
 public:
  template <typename T, typename... Args>
  ComponentPool<T>& Make(Args&&... args) {
    auto idx = rtti::GetClassIndex<T>();
    assert(pools_.find(idx) == pools_.end() && "component pool already made");
    auto ptr = std::make_unique<ComponentPool<T>>(std::forward<Args>(args)...);
    auto& ref = *ptr;
    pools_[idx] = std::move(ptr);
    return ref;
  }

  template <typename T>
  const ComponentPool<T>& Get() const {
    auto idx = rtti::GetClassIndex<T>();
    return static_cast<const ComponentPool<T>&>(*pools_.at(idx));
  }

  template <typename T>
  ComponentPool<T>& Get() {
    return const_cast<ComponentPool<T>&>(
        static_cast<const ComponentPoolManager&>(*this).Get<T>());
  }

  const IComponentPool& Get(rtti::ClassIndex idx) const {
    return *pools_.at(idx);
  }

  IComponentPool& Get(rtti::ClassIndex idx) { return *pools_.at(idx); }

 private:
  using Ptr = std::unique_ptr<IComponentPool>;
  using Map = std::map<rtti::ClassIndex, Ptr>;
  Map pools_;
};

}  // namespace einu