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

#include <memory>
#include <utility>

#include "einu-engine/core/internal/pool_policy.h"
#include "einu-engine/core/xnent.h"
#include "einu-engine/core/xnent_type_id.h"

namespace einu {

class IXnentPool {
 public:
  using size_type = std::size_t;
  using Policy = internal::PoolPolicy;

  virtual ~IXnentPool() = default;

  void AddPolicy(Policy&& policy, XnentTypeID id) {
    AddPolicyImpl(policy.init_size, policy.growth_func, id);
  }

  template <typename T>
  void AddPolicy(Policy&& policy) {
    AddPolicyImpl(policy.init_size, policy.growth_func, GetXnentTypeID<T>());
  }

  template <typename T>
  T& Acquire() {
    return static_cast<T&>(AcquireImpl(GetXnentTypeID<T>()));
  }

  Xnent& Acquire(XnentTypeID tid) { return AcquireImpl(tid); }

  template <typename T>
  void Release(T& comp) noexcept {
    ReleaseImpl(GetXnentTypeID<T>(), comp);
  }

  void Release(XnentTypeID tid, Xnent& comp) noexcept {
    ReleaseImpl(tid, comp);
  }

  template <typename T>
  size_type OnePoolSize() const noexcept {
    return OnePoolSizeImpl(GetXnentTypeID<T>());
  }

  size_type OnePoolSize(XnentTypeID tid) const noexcept {
    return OnePoolSizeImpl(tid);
  }

 protected:
  virtual void AddPolicyImpl(size_type init_size,
                             internal::GrowthFunc growth_func,
                             XnentTypeID id) = 0;
  virtual Xnent& AcquireImpl(XnentTypeID id) = 0;
  virtual void ReleaseImpl(XnentTypeID id, Xnent& comp) noexcept = 0;
  virtual size_type OnePoolSizeImpl(XnentTypeID id) const noexcept = 0;
};

}  // namespace einu
