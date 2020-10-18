#pragma once

#include <map>
#include <memory>

#include "einu-engine/core/component_pool.h"
#include "einu-engine/utility/rtti/class_index_storage.h"

namespace einu {

class ComponentPoolManager {
 public:
  template <typename T, typename... Args>
  XnentPool<T>& Make(Args&&... args) {
    auto idx = rtti::GetTypeID<T>();
    assert(pools_.find(idx) == pools_.end() && "component pool already made");
    auto ptr = std::make_unique<XnentPool<T>>(std::forward<Args>(args)...);
    auto& ref = *ptr;
    pools_[idx] = std::move(ptr);
    return ref;
  }

  template <typename T>
  const XnentPool<T>& Get() const {
    auto idx = rtti::GetTypeID<T>();
    return static_cast<const XnentPool<T>&>(*pools_.at(idx));
  }

  template <typename T>
  XnentPool<T>& Get() {
    return const_cast<XnentPool<T>&>(
        static_cast<const ComponentPoolManager&>(*this).Get<T>());
  }

  const IXnentPool& Get(rtti::TypeID idx) const {
    return *pools_.at(idx);
  }

  IXnentPool& Get(rtti::TypeID idx) { return *pools_.at(idx); }

 private:
  using Ptr = std::unique_ptr<IXnentPool>;
  using Map = std::map<rtti::TypeID, Ptr>;
  Map pools_;
};

}  // namespace einu