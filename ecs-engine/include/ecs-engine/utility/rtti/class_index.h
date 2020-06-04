#pragma once

#include <cstddef>

namespace ecs {
namespace rtti {

class ClassIndex {
 public:
  using IndexType = std::size_t;

  explicit ClassIndex(IndexType index = ~IndexType(0)) noexcept {
    index_ = index;
  }
  operator IndexType&() noexcept { return index_; }
  operator IndexType() const noexcept { return index_; }

 private:
  IndexType index_;
};

inline bool IsAssigned(ClassIndex idx) { return idx != ClassIndex(); }

template <typename T>
ClassIndex& GetClassIndex() {
  static auto index = ClassIndex();
  return index;
}

}  // namespace rtti
}  // namespace ecs
