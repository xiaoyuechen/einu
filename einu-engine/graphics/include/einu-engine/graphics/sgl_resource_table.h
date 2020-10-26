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

#include <absl/container/flat_hash_map.h>
#include <einu-engine/core/xnent.h>

#include <array>
#include <cstdint>
#include <string>
#include <utility>

#include "einu-engine/graphics/resource_type.h"

namespace einu {
namespace graphics {

struct TextureInfo {
  int width;
  int height;
};

namespace sgl {

struct ResourceTable : public Xnent {
  using Key = std::pair<ResourceType, std::string>;
  using Value = std::uint32_t;
  using Table = absl::flat_hash_map<Key, Value>;
  using TextureInfoTable = absl::flat_hash_map<std::string, TextureInfo>;

  Table table;
  TextureInfoTable texture_info_table;
};

}  // namespace sgl
}  // namespace graphics
}  // namespace einu