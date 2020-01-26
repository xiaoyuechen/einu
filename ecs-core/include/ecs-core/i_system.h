#pragma once
#include <tuple>

#include "component_mask.h"
#include "ecs-core/utility/algorithm.h"
#include "ecs-core/utility/pattern.h"
#include "ecs-core/utility/type_list.h"

namespace ecs {

class ISystem {
 public:
  virtual ~ISystem();
  virtual void Update(float dt);
};



class ExStoragePolicy {
 public:
  template <typename T>
  using Container = std::vector<T>;
};

template <typename RequiredCompTypeList,
          typename StoragePolicy = ExStoragePolicy>
class ExSystem {
 public:
  void UpdateComponentCache() {}

 private:
  using Tuple = typename TuplePtrOf<RequiredCompTypeList>::Tuple;
  template <typename T>
  using Container = typename StoragePolicy::Container;
  Container<Tuple> chache_;
};

template <typename... Components>
class System : public ISystem {
 public:
  const std::vector<std::tuple<Components*...>>& GetComponentCache() const {
    return component_cache_;
  }

  void UpdateComponentCache() {}

 private:
  std::vector<std::tuple<Components*...>> component_cache_;
};

//////////////////////////////////////////////////////////////////////////

inline ISystem::~ISystem() {}

inline void ISystem::Update(float) {}

}  // namespace ecs