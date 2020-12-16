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

#include "einu-engine/core/xnent_list.h"
#include "einu-engine/core/xnent_type_id.h"
#include "tplusplus/static_algo.h"
#include "tplusplus/type_list.h"

namespace einu {
namespace internal {

template <typename XnentList>
class XnentTypeIDRegister {
 public:
  XnentTypeIDRegister() noexcept {
    RequireUnique();

    tpp::static_for<0, kCount>([](auto i) {
      using Xnent = typename tpp::TypeAt<TypeList, i>::Type;
      SetXnentTypeID<Xnent>(XnentTypeID{i});
    });
  }

  ~XnentTypeIDRegister() noexcept {
    tpp::static_for<0, kCount>([](auto i) {
      using Xnent = typename tpp::TypeAt<TypeList, i>::Type;
      ResetXnentTypeID<Xnent>();
    });
  }

 private:
  using TypeList = typename ToTypeList<XnentList>::Type;
  static constexpr std::size_t kCount = tpp::Size<TypeList>::value;

  static constexpr void RequireUnique() noexcept {
    tpp::static_for<0, kCount>([](auto i) {
      using Xnent = typename tpp::TypeAt<TypeList, i>::Type;
      static_assert(tpp::CountType<TypeList, Xnent>::value == 1 &&
                    "Xnents must be unique");
    });
  }
};

}  // namespace internal
}  // namespace einu
