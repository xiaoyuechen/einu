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

#include <einu-engine/core/xnent.h>

#include <vector>

#include "src/agent.h"

namespace lol {
namespace cmp {

struct Agent : public einu::Xnent {
  AgentType type = AgentType::None;
};

struct GrassTag : public einu::Xnent {};

struct HerderTag : public einu::Xnent {};

struct Eat : public einu::Xnent {
  float eat_health_per_attack = 0;
  float absorption_rate = 0.5f;
};

struct Evade : public einu::Xnent {
  using Predators = std::vector<AgentInfo>;
  AgentType predator_signature = AgentType::None;
  Predators predators{};
  glm::vec2 evade_dest{};
  float evade_dist = 200.f;
};

struct Panick : public einu::Xnent {
  float remaining_panick_time = 0.0f;
  float max_panick_time = 3.0f;
};

struct Hunger : public einu::Xnent {
  float health_threashold = 100;
};

struct Hunt : public einu::Xnent {
  AgentType prey_signature = AgentType::None;
  AgentInfo current_prey{};
};

struct Memory : public einu::Xnent {
  std::vector<AgentInfo> memory;
};

struct Sense : public einu::Xnent {
  AgentType relevant_type_signature = AgentType::None;
  float sense_radius = 0;
};

struct Wander : public einu::Xnent {
  float time_since_last_destination_change = 0;
  float destination_change_interval = 2.f;
  float wander_radius = 10.f;
};

}  // namespace cmp
}  // namespace lol
