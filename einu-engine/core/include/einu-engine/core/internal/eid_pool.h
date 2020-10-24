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

#include <atomic>

#include "einu-engine/core/i_eid_pool.h"

namespace einu {
namespace internal {

class EIDPool final : public IEIDPool {
 private:
  EID AcquireImpl() noexcept override { return available_++; }

  void ReleaseImpl(EID eid) noexcept override {}

  std::atomic_uint32_t available_{0};
};

}  // namespace internal
}  // namespace einu
