#pragma once

#include <cstddef>
#include <type_traits>

namespace einu {
namespace rtti {

class TypeID {
 public:
  using IndexType = std::size_t;

  constexpr explicit TypeID(IndexType index = ~IndexType(0)) noexcept
      : index_(index) {}
  operator IndexType&() noexcept { return index_; }
  operator IndexType() const noexcept { return index_; }

 private:
  IndexType index_;
};

inline bool IsAssigned(TypeID id) noexcept { return id != TypeID(); }

namespace internal {

template <typename T>
struct TypeIDStorage {
  inline static TypeID value = TypeID();
};

}  // namespace internal

template <typename T>
void SetTypeID(TypeID id) noexcept {
  internal::TypeIDStorage<std::decay<T>::type>::value = id;
}

template <typename T>
TypeID GetTypeID() noexcept {
  return internal::TypeIDStorage<std::decay<T>::type>::value;
}

}  // namespace rtti
}  // namespace einu