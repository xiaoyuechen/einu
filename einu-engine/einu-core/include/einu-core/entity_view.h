#pragma once

#include <einu-tmp/static_algo.h>

#include "einu-core/i_entity_manager.h"

namespace einu {

template <typename XnentList>
struct TupleRefOf;

template <typename... Comps>
struct TupleRefOf<XnentList<Comps...>> {
  using Type = std::tuple<Comps&...>;
};

template <typename ComponentList>
class ComponentIterator;

template <typename... Comps>
class ComponentIterator<XnentList<Comps...>> {
 public:
  using VecItr = std::vector<Xnent*>::iterator;

  constexpr ComponentIterator(VecItr itr) noexcept
      : itr_(itr) {}

  constexpr ComponentIterator& operator++() noexcept {
    std::advance(itr_, sizeof...(Comps));
    return *this;
  }

  constexpr ComponentIterator operator++(int) noexcept {
    auto retval = *this;
    ++(*this);
    return retval;
  }

  constexpr bool operator==(ComponentIterator other) const noexcept {
    return itr_ == other.itr_;
  }

  constexpr bool operator!=(ComponentIterator other) const noexcept {
    return !(*this == other);
  }

  constexpr std::tuple<Comps&...> operator*() noexcept {
    return std::forward_as_tuple(DeRef<Comps>()...);
  }

 private:
  template <typename T>
  T& DeRef() noexcept {
    using TypeList = tmp::TypeList<Comps...>;
    return static_cast<T&>(**std::next(itr_, tmp::IndexOf<TypeList, T>::value));
  }

  VecItr itr_;
};

template <typename ComponentList>
class ComponentBuffer {
 public:
  constexpr ComponentBuffer(std::vector<Xnent*> comps)
      : comps_(comps) {}

  auto begin() noexcept {
    return ComponentIterator<ComponentList>{comps_.begin()};
  }

  auto end() noexcept {
    using TypeList = typename ToTypeList<ComponentList>::Type;
    return ComponentIterator<ComponentList>{
        std::next(comps_.begin(), comps_.size() - tmp::Size<TypeList>::value)};
  }

 private:
  std::vector<Xnent*>& comps_;
};

template <typename ComponentList>
class EntityView {
 public:
  using ComponentBuffer = ComponentBuffer<ComponentList>;

  void View(IEntityManager& ett_mgr) {
    Clear(ett_buffer_);
    ett_mgr.GetEntitiesWithComponents(ett_buffer_, ComponentList{});
  }

  ComponentBuffer GetComponents() noexcept {
    return ComponentBuffer{ett_buffer_.comps};
  }



 private:
  EntityBuffer ett_buffer_;
};

}  // namespace einu