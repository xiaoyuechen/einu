#pragma once

#include <type_traits>

#include "einu-engine/core/i_component.h"
#include "einu-engine/utility/pool/fixed_size_pool.h"

namespace einu {

class IComponentPool {
 public:
  virtual ~IComponentPool() = default;
  virtual void Recall(const IComponent& comp) = 0;
  virtual IComponent& Acquire() = 0;
};

template <typename T>
class ComponentPool : public FixedSizePool<T>, public IComponentPool {
  static_assert(std::is_base_of<IComponent, T>::value &&
                "<T> must inherit from <IComponent>");

 public:
  using Pool = FixedSizePool<T>;
  using Pool::Pool;

  virtual void Recall(const IComponent& comp) override {
    Pool::Recall(static_cast<const T&>(comp));
  }

  virtual IComponent& Acquire() override { return Pool::Acquire(); }
};

}  // namespace einu
