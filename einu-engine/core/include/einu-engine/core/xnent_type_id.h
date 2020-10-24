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

#include <einu-engine/core/rtti/type_id.h>

#include <cassert>
#include <type_traits>

#include "einu-engine/core/xnent.h"

namespace einu {

class XnentTypeID : public rtti::TypeID {
 public:
  using rtti::TypeID::TypeID;
};

template <typename T>
void SetXnentTypeID(XnentTypeID id) noexcept {
  static_assert(std::is_base_of<Xnent, T>::value &&
                "<Xnent> must be base of <T>");
  assert(!rtti::IsAssigned(GetXnentTypeID<T>()) &&
         "xnent id is already assigned");
  rtti::SetTypeID<T>(id);
}

template <typename T>
XnentTypeID GetXnentTypeID() noexcept {
  static_assert(std::is_base_of<Xnent, T>::value &&
                "<Xnent> must be base of <T>");
  return XnentTypeID(rtti::GetTypeID<T>());
}

template <typename T>
void ResetXnentTypeID() noexcept {
  static_assert(std::is_base_of<Xnent, T>::value &&
                "<Xnent> must be base of <T>");
  rtti::SetTypeID<T>(XnentTypeID{});
}

}  // namespace einu
