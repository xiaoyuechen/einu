#pragma once

#include <tuple>

#include "einu-core/i_entity_manager.h"
#include "einu-core/xnent_list.h"

namespace einu {

template <typename ComponentList>
class ComponentIterator;

template <typename... Comps>
class ComponentIterator<XnentList<Comps...>> {
 public:
  using Itr = std::vector<Xnent*>::const_iterator;

  constexpr ComponentIterator(Itr itr) noexcept
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

  constexpr std::tuple<Comps&...> operator*() const noexcept {
    return std::forward_as_tuple(DeRef<Comps>()...);
  }

 private:
  template <typename T>
  T& DeRef() const noexcept {
    using TypeList = tmp::TypeList<Comps...>;
    return static_cast<T&>(**std::next(itr_, tmp::IndexOf<TypeList, T>::value));
  }

  Itr itr_;
};

template <typename ComponentList>
class ComponentBuffer {
 public:
  constexpr ComponentBuffer(const std::vector<Xnent*>& comps) noexcept
      : comps_(comps) {}

  auto begin() const noexcept {
    return ComponentIterator<ComponentList>{comps_.begin()};
  }

  auto end() const noexcept {
    return ComponentIterator<ComponentList>{comps_.end()};
  }

 private:
  const std::vector<Xnent*>& comps_;
};

class EIDBuffer {
 public:
  constexpr EIDBuffer(const std::vector<EID>& eids) noexcept
      : eids_(eids) {}

  auto begin() const noexcept { return eids_.begin(); }

  auto end() const noexcept { return eids_.end(); }

 private:
  const std::vector<EID>& eids_;
};

template <typename ComponentList>
class EntityView {
 public:
  using ComponentBuffer = ComponentBuffer<ComponentList>;

  void View(IEntityManager& ett_mgr) {
    Clear(ett_buffer_);
    ett_mgr.GetEntitiesWithComponents(ett_buffer_, ComponentList{});
  }

  ComponentBuffer Components() const noexcept {
    return ComponentBuffer{ett_buffer_.comps};
  }

  EIDBuffer EIDs() const noexcept { return EIDBuffer{ett_buffer_.eids}; }

 private:
  EntityBuffer ett_buffer_;
};

}  // namespace einu