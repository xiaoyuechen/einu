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

#include "einu-engine/core/xnent.h"

namespace lol {
namespace cmp {

struct Health : einu::Xnent {
  float health = 100.f;
  float max_health = 120.f;
};

constexpr float AddHealth(Health& comp, float delta) noexcept {
  comp.health += delta;
  comp.health = std::clamp(comp.health, 0.f, comp.max_health);
  return comp.health;
}

struct HealthLoss : einu::Xnent {
  float loss_speed = 0;
};

}  // namespace cmp
}  // namespace lol
