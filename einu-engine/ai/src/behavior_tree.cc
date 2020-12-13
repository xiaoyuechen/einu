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

#include "einu-engine/ai/behavior_tree.h"

#include <utility>

namespace einu {
namespace ai {
namespace bt {

Result Root::Run(const ArgPack& args) {
  auto& child = GetChildren()[0];
  child->Run(args);
  return Result::Success;
}

Result Sequence::Run(const ArgPack& args) {
  for (auto&& child : GetChildren()) {
    auto result = child->Run(args);
    if (result == Result::Running) {
      return Result::Running;
    }
    if (result == Result::Failure) {
      return Result::Failure;
    }
  }
  return Result::Success;
}

Result Selector::Run(const ArgPack& args) {
  for (auto&& child : GetChildren()) {
    auto result = child->Run(args);
    if (result == Result::Running) {
      return Result::Running;
    }
    if (result == Result::Success) {
      return Result::Success;
    }
  }
  return Result::Failure;
}

Result Inverter::Run(const ArgPack& args) {
  auto& child = GetChildren()[0];
  auto result = child->Run(args);
  if (result == Result::Running) {
    return Result::Running;
  }
  if (result == Result::Failure) {
    return Result::Success;
  }
  if (result == Result::Success) {
    return Result::Failure;
  }
  return Result::Failure;
}

Result Succeeder::Run(const ArgPack& args) {
  auto& child = GetChildren()[0];
  child->Run(args);
  return Result::Success;
}

}  // namespace bt
}  // namespace ai
}  // namespace einu
