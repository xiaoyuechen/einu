#pragma once

#include <vector>

#include "einu-core/component_list.h"
#include "einu-core/internal/component_index.h"

namespace einu {
namespace internal {

class ComponentIndexList {
 public:
  template <typename... Ts>
  explicit ComponentIndexList(ComponentList<Ts...>) {
    (list_.push_back(GetComponentIndex<Ts>()), ...);
  }

  auto begin() const { return list_.begin(); }
  auto end() const { return list_.end(); }

 private:
  using List = std::vector<ComponentIndex>;
  List list_;
};

template <typename... Ts>
const ComponentIndexList& GetComponentIndexList(
    ComponentList<Ts...> comp_list) {
  static ComponentIndexList idx_list(comp_list);
  return idx_list;
}

}  // namespace internal
}  // namespace einu