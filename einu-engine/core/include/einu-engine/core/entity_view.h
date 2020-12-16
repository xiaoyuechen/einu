// Copyright (C) 2020  Xiaoyue Chen
//
// This file is part of EINU Engine.
// See <https://github.com/xiaoyuechen/einu.git>.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <tuple>
#include <vector>

#include "einu-engine/core/i_entity_manager.h"
#include "einu-engine/core/xnent_list.h"

namespace einu {

template <typename ComponentList>
class ComponentIterator;

template <typename... Comps>
class ComponentIterator<XnentList<Comps...>> {
 public:
  using Itr = std::vector<Xnent*>::const_iterator;

  constexpr explicit ComponentIterator(Itr itr) noexcept : itr_(itr) {}

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
    using TypeList = tpp::TypeList<Comps...>;
    return static_cast<T&>(**std::next(itr_, tpp::IndexOf<TypeList, T>::value));
  }

  Itr itr_;
};

template <typename ComponentList>
class ComponentBufferView {
 public:
  constexpr explicit ComponentBufferView(
      const std::vector<Xnent*>& comps) noexcept
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

class EIDBufferView {
 public:
  constexpr explicit EIDBufferView(const std::vector<EID>& eids) noexcept
      : eids_(eids) {}

  auto begin() const noexcept { return eids_.begin(); }

  auto end() const noexcept { return eids_.end(); }

 private:
  const std::vector<EID>& eids_;
};

template <typename ComponentList>
class EntityView {
 public:
  using ComponentsView = ComponentBufferView<ComponentList>;

  void View(IEntityManager& ett_mgr) {
    Clear(ett_buffer_);
    ett_mgr.GetEntitiesWithComponents(ett_buffer_, ComponentList{});
  }

  ComponentsView Components() const noexcept {
    return ComponentsView{ett_buffer_.comps};
  }

  EIDBufferView EIDs() const noexcept {
    return EIDBufferView{ett_buffer_.eids};
  }

  auto Size() const noexcept { return ett_buffer_.eids.size(); }

 private:
  EntityBuffer ett_buffer_;
};

}  // namespace einu
