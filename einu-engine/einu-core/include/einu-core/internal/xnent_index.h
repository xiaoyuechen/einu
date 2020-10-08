#pragma once

#include <einu-rtti/class_index_storage.h>

#include <type_traits>

#include "einu-core/xnent.h"

namespace einu {
namespace internal {

class XnentIndex : public rtti::ClassIndex {
 public:
  using rtti::ClassIndex::ClassIndex;
};

template <typename T>
void SetXnentIndex(XnentIndex idx) noexcept {
  static_assert(std::is_base_of<Xnent, T>::value &&
                "<Xnent> must be base of <T>");
  rtti::SetClassIndex<T>(idx);
}

template <typename T>
XnentIndex GetXnentIndex() noexcept {
  static_assert(std::is_base_of<Xnent, T>::value &&
                "<Xnent> must be base of <T>");
  return XnentIndex(rtti::GetClassIndex<T>());
}

}  // namespace internal
}  // namespace einu