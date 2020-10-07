#pragma once

#include <vector>

#include "einu-core/component_list.h"
#include "einu-core/internal/component_index.h"

namespace einu {
namespace internal {

class ComponentIndexList {
 public:
  template <typename... Ts>
  constexpr explicit ComponentIndexList(ComponentList<Ts...>)
      : list_{GetComponentIndex<Ts>()...} {}

  auto begin() const noexcept { return list_.begin(); }
  auto end() const noexcept { return list_.end(); }

 private:
  using List = std::vector<ComponentIndex>;
  List list_;
};

template <typename... Ts>
const ComponentIndexList& GetComponentIndexList(
    ComponentList<Ts...> comp_list) {
  static auto& idx_list = *new ComponentIndexList(comp_list);
  return idx_list;
}

}  // namespace internal
}  // namespace einu