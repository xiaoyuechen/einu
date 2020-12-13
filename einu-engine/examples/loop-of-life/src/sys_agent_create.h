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

#include "einu-engine/common/transform.h"
#include "einu-engine/core/i_entity_manager.h"
#include "src/agent.h"

namespace lol {
namespace sys {

template <AgentType t>
einu::EID CreateAgent(einu::IEntityManager& ett_mgr,
                      const einu::Transform& transform);

template <>
einu::EID CreateAgent<AgentType::Sheep>(einu::IEntityManager& ett_mgr,
                                        const einu::Transform& transform);

template <>
einu::EID CreateAgent<AgentType::Wolf>(einu::IEntityManager& ett_mgr,
                                       const einu::Transform& transform);

template <>
einu::EID CreateAgent<AgentType::Grass>(einu::IEntityManager& ett_mgr,
                                        const einu::Transform& transform);

template <>
einu::EID CreateAgent<AgentType::Herder>(einu::IEntityManager& ett_mgr,
                                         const einu::Transform& transform);

static constexpr const char* kSheepSpriteName = "sheep";
einu::EID CreateSheep(einu::IEntityManager& ett_mgr,
                      const einu::Transform& transform);

static constexpr const char* kWolfSpriteName = "wolf";
einu::EID CreateWolf(einu::IEntityManager& ett_mgr,
                     const einu::Transform& transform);

static constexpr const char* kGrassSpriteName = "grass";
einu::EID CreateGrass(einu::IEntityManager& ett_mgr,
                      const einu::Transform& transform);

static constexpr const char* kHerderSpriteName = "herder";
einu::EID CreateHerder(einu::IEntityManager& ett_mgr,
                       const einu::Transform& transform);

}  // namespace sys
}  // namespace lol
