#pragma once

#include <cstddef>
#include <type_traits>

namespace einu {
namespace rtti {

class ClassIndex {
 public:
  using IndexType = std::size_t;

  constexpr explicit ClassIndex(IndexType index = ~IndexType(0)) noexcept
      : index_(index) {}
  operator IndexType&() noexcept { return index_; }
  operator IndexType() const noexcept { return index_; }

 private:
  IndexType index_;
};

inline bool IsAssigned(ClassIndex idx) noexcept { return idx != ClassIndex(); }

namespace internal {

template <typename T>
struct ClassIndexStorage {
  inline static ClassIndex value = ClassIndex();
};

}  // namespace internal

template <typename T>
void SetClassIndex(ClassIndex idx) noexcept {
  internal::ClassIndexStorage<std::decay<T>::type>::value = idx;
}

template <typename T>
ClassIndex GetClassIndex() noexcept {
  return internal::ClassIndexStorage<std::decay<T>::type>::value;
}

}  // namespace rtti
}  // namespace einu