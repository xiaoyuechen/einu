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

#include <einu-engine/core/util/enum.h>
#include <einu-engine/core/xnent.h>

namespace lol {
namespace cmp {

struct AgentType : public einu::Xnent {
  enum class Type : std::uint8_t {
    NONE = 0,
    GRASS = 1 << 0,
    SHEEP = 1 << 1,
    WOLF = 1 << 2,
    CROW = 1 << 3,
  };

  Type type = Type::NONE;
};

AgentType::Type GetSignatureAll() { return static_cast<AgentType>(~0u); }

}  // namespace cmp
}  // namespace lol

namespace einu {
namespace util {

template <>
struct EnableBitMaskOperators<AgentType> {
  static constexpr bool enable = true;
};
}  // namespace util
}  // namespace einu
