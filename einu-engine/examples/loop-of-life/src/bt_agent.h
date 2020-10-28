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

#include <einu-engine/ai/behavior_tree.h>
#include <einu-engine/ai/bt_move_to.h>
#include <einu-engine/common/sgl_time.h>
#include <einu-engine/core/i_entity_manager.h>

namespace lol {
namespace ai {
namespace bt {

einu::ai::bt::Root BuildSheepBT(einu::IEntityManager& ett_mgr);

using Result = einu::ai::bt::Result;
using ArgPack = einu::ai::bt::ArgPack;
using Node = einu::ai::bt::Node;

class EatPrey final : public Node {
 public:
  explicit EatPrey(einu::IEntityManager& ett_mgr);
  Result Run(const ArgPack& args) override;

 private:
  einu::IEntityManager& ett_mgr_;
};

class FindPredator final : public Node {
 public:
  Result Run(const ArgPack& args) override;
};

class FindPrey final : public Node {
 public:
  Result Run(const ArgPack& args) override;
};

class HasTargetedPrey final : public Node {
 public:
  explicit HasTargetedPrey(const einu::IEntityManager& ett_mgr);

  Result Run(const ArgPack& args) override;

 private:
  const einu::IEntityManager& ett_mgr_;
};

class IsHungry final : public Node {
 public:
  Result Run(const ArgPack& args) override;
};

class TrackPrey final : public Node {
 public:
  Result Run(const ArgPack& args) override;
};

class Escape final : public Node {
 public:
  Result Run(const ArgPack& args) override;
};

class ChooseRandomDestination final : public Node {
 public:
  explicit ChooseRandomDestination(const einu::IEntityManager& ett_mgr);

  Result Run(const ArgPack& args) override;

 private:
  const einu::IEntityManager& ett_mgr_;
};

class IsPanicking final : public Node {
 public:
  Result Run(const ArgPack& args) override;
};

}  // namespace bt
}  // namespace ai
}  // namespace lol
