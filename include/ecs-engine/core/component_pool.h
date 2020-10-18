#pragma once

#include <type_traits>

#include "einu-engine/core/i_component.h"
#include "einu-engine/utility/pool/fixed_size_pool.h"

namespace einu {

class IXnentPool {
 public:
  virtual ~IXnentPool() = default;
  virtual void Recall(const Xnent& comp) = 0;
  virtual Xnent& Acquire() = 0;
};

template <typename T>
class XnentPool : public FixedSizePool<T>, public IXnentPool {
  static_assert(std::is_base_of<Xnent, T>::value &&
                "<T> must inherit from <Xnent>");

 public:
  using Pool = FixedSizePool<T>;
  using Pool::Pool;

  virtual void Recall(const Xnent& comp) override {
    Pool::Recall(static_cast<const T&>(comp));
  }

  virtual Xnent& Acquire() override { return Pool::Acquire(); }
};

}  // namespace einu
