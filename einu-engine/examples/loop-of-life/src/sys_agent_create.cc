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

#include "src/sys_agent_create.h"

#include <einu-engine/ai/cmp_destination.h>
#include <einu-engine/common/cmp_movement.h>
#include <einu-engine/common/cmp_transform.h>
#include <einu-engine/common/random.h>
#include <einu-engine/core/util/enum.h>
#include <einu-engine/graphics/cmp_sprite.h>

#include "src/cmp_agent.h"
#include "src/cmp_health.h"

namespace lol {
namespace sys {

template <>
einu::EID CreateAgent<AgentType::Sheep>(einu::IEntityManager& ett_mgr,
                                        const einu::Transform& transform) {
  return CreateSheep(ett_mgr, transform);
}

template <>
einu::EID CreateAgent<AgentType::Wolf>(einu::IEntityManager& ett_mgr,
                                       const einu::Transform& transform) {
  return CreateWolf(ett_mgr, transform);
}

template <>
einu::EID CreateAgent<AgentType::Grass>(einu::IEntityManager& ett_mgr,
                                        const einu::Transform& transform) {
  return CreateGrass(ett_mgr, transform);
}

template <>
einu::EID CreateAgent<AgentType::Herder>(einu::IEntityManager& ett_mgr,
                                         const einu::Transform& transform) {
  return CreateHerder(ett_mgr, transform);
}

einu::EID CreateSheep(einu::IEntityManager& ett_mgr,
                      const einu::Transform& transform) {
  auto ett = ett_mgr.CreateEntity();

  auto& sprite = ett_mgr.AddComponent<einu::graphics::cmp::Sprite>(ett);
  sprite.color = glm::vec4{255, 255, 255, 255};
  sprite.sprite_name = kSheepSpriteName;

  ett_mgr.AddComponent<einu::cmp::Transform>(ett) =
      einu::cmp::Transform{transform};

  auto& movement = ett_mgr.AddComponent<einu::cmp::Movement>(ett);
  movement.max_speed = 14;

  ett_mgr.AddComponent<einu::ai::cmp::Destination>(ett);

  ett_mgr.AddComponent<cmp::Agent>(ett).type = AgentType::Sheep;

  auto& eat = ett_mgr.AddComponent<cmp::Eat>(ett);
  eat.eat_health_per_attack = 120.f;
  eat.absorption_rate = 0.5f;

  ett_mgr.AddComponent<cmp::Evade>(ett).predator_signature = AgentType::Wolf;

  ett_mgr.AddComponent<cmp::Health>(ett);

  ett_mgr.AddComponent<cmp::HealthLoss>(ett).loss_speed = 5.f;

  ett_mgr.AddComponent<cmp::Hunger>(ett).health_threashold = 100.f;

  ett_mgr.AddComponent<cmp::Hunt>(ett).prey_signature = AgentType::Grass;

  ett_mgr.AddComponent<cmp::Memory>(ett);

  auto& panick = ett_mgr.AddComponent<cmp::Panick>(ett);
  panick.max_panick_time = 1.0f;

  auto& reproduce = ett_mgr.AddComponent<cmp::Reproduce>(ett);
  reproduce.health_threadhold = 110;
  reproduce.cost_health_ratio = 0.4f;
  reproduce.transform = transform;

  auto& sense = ett_mgr.AddComponent<cmp::Sense>(ett);
  using einu::util::operator|;
  sense.relevant_type_signature =
      AgentType::Wolf | AgentType::Grass | AgentType::Herder;
  sense.sense_radius = 200.f;

  auto& wander = ett_mgr.AddComponent<cmp::Wander>(ett);
  wander.time_since_last_destination_change = 99999;
  wander.wander_radius = 50;

  return ett;
}

einu::EID CreateWolf(einu::IEntityManager& ett_mgr,
                     const einu::Transform& transform) {
  auto ett = ett_mgr.CreateEntity();

  auto& sprite = ett_mgr.AddComponent<einu::graphics::cmp::Sprite>(ett);
  sprite.color = glm::vec4{100, 100, 100, 255};
  sprite.sprite_name = kWolfSpriteName;

  ett_mgr.AddComponent<einu::cmp::Transform>(ett) =
      einu::cmp::Transform{transform};

  auto& movement = ett_mgr.AddComponent<einu::cmp::Movement>(ett);
  movement.max_speed = 40;

  auto& dest = ett_mgr.AddComponent<einu::ai::cmp::Destination>(ett);

  ett_mgr.AddComponent<cmp::Agent>(ett).type = AgentType::Wolf;

  auto& eat = ett_mgr.AddComponent<cmp::Eat>(ett);
  eat.eat_health_per_attack = 100.f;
  eat.absorption_rate = 0.4f;

  ett_mgr.AddComponent<cmp::Evade>(ett).predator_signature = AgentType::Herder;

  ett_mgr.AddComponent<cmp::Health>(ett);

  ett_mgr.AddComponent<cmp::HealthLoss>(ett).loss_speed = 5.f;

  ett_mgr.AddComponent<cmp::Hunger>(ett).health_threashold = 120.f;

  ett_mgr.AddComponent<cmp::Hunt>(ett).prey_signature = AgentType::Sheep;

  ett_mgr.AddComponent<cmp::Memory>(ett);

  auto& panick = ett_mgr.AddComponent<cmp::Panick>(ett);
  panick.max_panick_time = 1.0f;

  auto& reproduce = ett_mgr.AddComponent<cmp::Reproduce>(ett);
  reproduce.health_threadhold = 110;
  reproduce.cost_health_ratio = 0.3f;
  reproduce.transform = transform;

  auto& sense = ett_mgr.AddComponent<cmp::Sense>(ett);
  using einu::util::operator|;
  sense.relevant_type_signature = AgentType::Sheep | AgentType::Herder;
  sense.sense_radius = 200.f;

  auto& wander = ett_mgr.AddComponent<cmp::Wander>(ett);
  wander.time_since_last_destination_change = 99999;
  wander.wander_radius = 100;

  return ett;
}

einu::EID CreateGrass(einu::IEntityManager& ett_mgr,
                      const einu::Transform& transform) {
  auto ett = ett_mgr.CreateEntity();

  ett_mgr.AddComponent<cmp::GrassTag>(ett);

  auto& sprite = ett_mgr.AddComponent<einu::graphics::cmp::Sprite>(ett);
  sprite.color = glm::vec4{50, 255, 50, 255};
  sprite.sprite_name = kGrassSpriteName;

  ett_mgr.AddComponent<einu::cmp::Transform>(ett) =
      einu::cmp::Transform{transform};

  ett_mgr.AddComponent<cmp::Agent>(ett).type = AgentType::Grass;

  ett_mgr.AddComponent<cmp::GainHealth>(ett);

  ett_mgr.AddComponent<cmp::Health>(ett);

  ett_mgr.AddComponent<cmp::HealthLoss>(ett).loss_speed = 1.f;

  ett_mgr.AddComponent<cmp::Memory>(ett);

  auto& reproduce = ett_mgr.AddComponent<cmp::Reproduce>(ett);
  reproduce.health_threadhold = 110;
  reproduce.cost_health_ratio = 0.5f;
  reproduce.transform = transform;

  auto& sense = ett_mgr.AddComponent<cmp::Sense>(ett);
  using einu::util::operator|;
  sense.relevant_type_signature =
      AgentType::Grass | AgentType::Herder | AgentType::Sheep | AgentType::Wolf;
  sense.sense_radius = 15.f;

  return ett;
}

einu::EID CreateHerder(einu::IEntityManager& ett_mgr,
                       const einu::Transform& transform) {
  auto ett = ett_mgr.CreateEntity();

  ett_mgr.AddComponent<cmp::HerderTag>(ett);

  auto& sprite = ett_mgr.AddComponent<einu::graphics::cmp::Sprite>(ett);
  sprite.color = glm::vec4{255, 255, 0, 255};
  sprite.sprite_name = kHerderSpriteName;

  ett_mgr.AddComponent<einu::cmp::Transform>(ett) =
      einu::cmp::Transform{transform};

  auto& movement = ett_mgr.AddComponent<einu::cmp::Movement>(ett);
  movement.max_speed = 30;

  ett_mgr.AddComponent<einu::ai::cmp::Destination>(ett);

  ett_mgr.AddComponent<cmp::Agent>(ett).type = AgentType::Herder;

  auto& eat = ett_mgr.AddComponent<cmp::Eat>(ett);
  eat.eat_health_per_attack = 1.f;
  eat.absorption_rate = 0.5f;

  ett_mgr.AddComponent<cmp::Health>(ett);

  ett_mgr.AddComponent<cmp::Hunt>(ett).prey_signature = AgentType::Wolf;

  ett_mgr.AddComponent<cmp::Memory>(ett);

  auto& sense = ett_mgr.AddComponent<cmp::Sense>(ett);
  sense.relevant_type_signature = AgentType::Wolf;
  sense.sense_radius = 1000.f;

  auto& wander = ett_mgr.AddComponent<cmp::Wander>(ett);
  wander.time_since_last_destination_change = 99999;
  wander.wander_radius = 50;

  return ett;
}

}  // namespace sys
}  // namespace lol
