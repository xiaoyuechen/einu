#pragma once

#include <cassert>

#include "ecs-engine/utility/misc/counter.h"
#include "ecs-engine/utility/rtti/class_index_storage.h"

namespace ecs {
namespace rtti {

class ClassIndexRegister {
 public:
  using size_type = std::size_t;

  template <typename T>
  void Register(ClassIndex idx) noexcept {
    auto& idx0 = GetClassIndex<T>();
    assert(!IsAssigned(idx0));
    idx0 = idx;
    counter_.CountUp();
  }

  size_type GetRegisteredCount() const noexcept { return counter_.GetCount(); }

 private:
  misc::Counter<size_type> counter_;
};

}  // namespace rtti
}  // namespace ecs
