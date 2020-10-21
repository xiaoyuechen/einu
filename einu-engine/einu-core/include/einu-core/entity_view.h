#pragma once

#include "einu-core/i_entity_manager.h"

namespace einu {

template <typename XnentList>
struct TupleRefOf;

template <typename... Comps>
struct TupleRefOf<XnentList<Comps...>> {
  using Type = std::tuple<Comps&...>;
};

template <typename... Comps>
class ComponentIterator {
 public:
  using VecItr = std::vector<Xnent*>::iterator;

  ComponentIterator(VecItr itr)
      : itr_(itr_) {}

  ComponentIterator& operator++() {}

  ComponentIterator operator++(int) {
    auto retval = *this;
    ++(*this);
    return retval;
  }

  bool operator==(ComponentIterator other) const {
    return ((std::get<Itrs>(itrs_) == std::get<Itrs>(other.itrs_)) && ...);
  }

  bool operator!=(ComponentIterator other) const { return !(*this == other); }

  auto operator*() {
    auto itr = itr_;
    return std::forward_as_tuple(static_cast<Comps&>(**(itr++))...);
  }

 private:
  VecItr itr_;
};

template <typename ComponentList>
class EntityView {
 public:
  class ComponentItr {
   public:
   private:
    std::vector<Xnent*> comps_;
  };

  void View(IEntityManager& ett_mgr) {
    Clear(ett_buffer_);
    ett_mgr.GetEntitiesWithComponents(ett_buffer_, ComponentList{});
  }

 private:
  EntityBuffer ett_buffer_;
};

}  // namespace einu