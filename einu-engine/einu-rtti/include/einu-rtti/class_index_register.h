#pragma once

#include <cassert>

#include "einu-rtti/class_index_storage.h"

namespace einu {
namespace rtti {

class ClassIndexRegister {
 public:
  using size_type = std::size_t;

  template <typename T>
  void Register(ClassIndex idx) noexcept {
    auto& idx0 = detail::ClassIndexStorage<T>::value;
    assert(!IsAssigned(idx0));
    idx0 = idx;
    ++count_;
  }

  size_type GetRegisteredCount() const noexcept { return count_; }

 private:
  size_type count_ = 0;
};

}  // namespace rtti
}  // namespace einu
