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

#include <einu-engine/common/transform.h>
#include <einu-engine/core/i_entity_manager.h>

namespace astar {
namespace sys {

static constexpr const char* kCellFrameSprite = "cell-frame";
einu::EID CreateCellFrame(einu::IEntityManager& ett_mgr,
                          const einu::Transform& transform);

static constexpr const char* kCellBlockSprite = "cell-block";
einu::EID CreateCellBlock(einu::IEntityManager& ett_mgr,
                          const einu::Transform& transform);

static constexpr const char* kSpaceshipSprite = "spaceship";
einu::EID CreateSpaceship(einu::IEntityManager& ett_mgr,
                          const einu::Transform& transform);

static constexpr const char* kTradingPostSprite = "spaceship";
einu::EID CreateTradingPost(einu::IEntityManager& ett_mgr,
                            const einu::Transform& transform);

static constexpr const char* kStarSprite = "star";
einu::EID CreateStar(einu::IEntityManager& ett_mgr,
                     const einu::Transform& transform);

static constexpr const char* kStarchaserSprite = "starchaser";
einu::EID CreateStarchaser(einu::IEntityManager& ett_mgr,
                           const einu::Transform& transform);

}  // namespace sys
}  // namespace astar
