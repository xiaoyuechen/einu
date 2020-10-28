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

#include "src/bt_agent.h"

#include <einu-engine/ai/cmp_destination.h>
#include <einu-engine/common/cmp_transform.h>
#include <einu-engine/common/random.h>
#include <einu-engine/common/sgl_time.h>

#include <utility>

#include "src/cmp_agent.h"
#include "src/cmp_health.h"

namespace lol {
namespace ai {
namespace bt {

einu::ai::bt::Root BuildSheepBT(einu::IEntityManager& ett_mgr) {
  using namespace einu::ai::bt;  // NOLINT
  auto root = Root();
  {
    auto& slc = root.AddChild<Selector>();
    {
      auto& evade_seq = slc.AddChild<Sequence>();
      {
        evade_seq.AddChild<FindPredator>();
        evade_seq.AddChild<Escape>();
      }

      auto& hunt_seq = slc.AddChild<Sequence>();
      {
        hunt_seq.AddChild<IsHungry>();
        hunt_seq.AddChild<FindPrey>();
        hunt_seq.AddChild<TrackPrey>();
        hunt_seq.AddChild<MoveTo>();
        hunt_seq.AddChild<EatPrey>(ett_mgr);
      }

      auto& wander_seq = slc.AddChild<Sequence>();
      {
        wander_seq.AddChild<ChooseRandomDestination>(ett_mgr);
        wander_seq.AddChild<MoveTo>();
      }
    }
  }

  auto& seq = root.AddChild<Sequence>();
  seq.AddChild<MoveTo>();
  return std::move(root);
}

EatPrey::EatPrey(einu::IEntityManager& ett_mgr) : ett_mgr_{ett_mgr} {}

void Eat(const cmp::Eat& eat, cmp::Health& self_health,
         cmp::Health& prey_health) {
  float eaten_health = eat.eat_health_per_attack;
  if (prey_health.health < eaten_health) {
    eaten_health = prey_health.health;
  }
  AddHealth(prey_health, -eaten_health);
  AddHealth(self_health, eat.absorption_rate * eaten_health);
}

Result EatPrey::Run(const ArgPack& args) {
  auto& hunt = args.GetComponent<cmp::Hunt>();
  auto& eat = args.GetComponent<cmp::Eat>();
  auto& health = args.GetComponent<cmp::Health>();
  auto& prey_health = ett_mgr_.GetComponent<cmp::Health>(hunt.current_prey);
  Eat(eat, health, prey_health);
  if (prey_health.health == 0) {
    return Result::Success;
  }
  return Result::Running;
}

ChooseRandomDestination::ChooseRandomDestination(einu::IEntityManager& ett_mgr)
    : ett_mgr_{ett_mgr} {}

Result ChooseRandomDestination::Run(const ArgPack& args) {
  auto& wander = args.GetComponent<cmp::Wander>();
  auto& transform = args.GetComponent<const einu::common::cmp::Transform>();
  auto& dest = args.GetComponent<einu::ai::cmp::Destination>();
  auto& time = ett_mgr_.GetSinglenent<const einu::common::sgl::Time>();

  if ((wander.time_since_last_destination_change +=
       einu::common::sgl::DeltaSeconds(time)) >
      wander.destination_change_interval) {
    auto wander_dir = glm::vec3(einu::common::RandomUniform(-1.f, 1.f),
                                einu::common::RandomUniform(-1.f, 1.f), 0);
    auto delta = wander_dir * wander.wander_radius;
    dest.destination = transform.GetPosition() + delta;
    wander.time_since_last_destination_change = 0;
  }

  return Result::Success;
}

}  // namespace bt
}  // namespace ai
}  // namespace lol
