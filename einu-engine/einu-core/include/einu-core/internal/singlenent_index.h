#pragma once

#include <einu-rtti/class_index_storage.h>

#include <type_traits>

#include "einu-core/i_singlenent.h"

namespace einu {
namespace internal {

class SinglenentIndex : public rtti::ClassIndex {
 public:
  using rtti::ClassIndex::ClassIndex;
};

template <typename T>
void SetSinglenentIndex(SinglenentIndex idx) {
  static_assert(std::is_base_of<ISinglenent, T>::value &&
                "<ISinglenent> must be base of <T>");
  rtti::SetClassIndex<T>(idx);
}

template <typename T>
SinglenentIndex GetSinglenentIndex() {
  static_assert(std::is_base_of<ISinglenent, T>::value &&
                "<ISinglenent> must be base of <T>");
  return SinglenentIndex(rtti::GetClassIndex<T>());
}

}  // namespace internal
}  // namespace einu