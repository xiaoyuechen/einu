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

#include <cstdint>
#include <functional>

#include "einu-engine/graphics/sys_resource.h"

namespace einu {
namespace graphics {
namespace sys {

using GenFunc = std::function<std::uint32_t()>;

inline void CreateHelper(sgl::ResourceTable& resource_table, ResourceType type,
                         const char* name, GenFunc gen_func) {
  auto rsc = gen_func();
  using Key = sgl::ResourceTable::Key;
  resource_table.table.emplace(Key{type, name}, rsc);
}

using DeleteFunc = std::function<void(std::uint32_t)>;

inline void DestroyHelper(sgl::ResourceTable& resource_table, ResourceType type,
                          const char* name, DeleteFunc delete_func) {
  using Key = sgl::ResourceTable::Key;
  using Type = ResourceType;
  auto it = resource_table.table.find(Key{type, name});
  delete_func(it->second);
  resource_table.table.erase(it);
}

}  // namespace sys
}  // namespace graphics
}  // namespace einu
