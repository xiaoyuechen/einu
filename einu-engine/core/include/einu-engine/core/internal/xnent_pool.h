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

#include <array>
#include <cassert>
#include <memory>
#include <utility>
#include <variant>

#include "einu-engine/core/i_xnent_pool.h"
#include "einu-engine/core/util/object_pool.h"
#include "einu-engine/core/xnent_list.h"

namespace einu {
namespace internal {

template <typename Comp>
class OneXnentPool {
 public:
  using size_type = std::size_t;
  using GrowthFunc = std::function<size_type(size_type)>;

  void SetValue(std::unique_ptr<Xnent> value) noexcept {
    auto ptr = value.release();
    auto v = std::unique_ptr<Comp>(reinterpret_cast<Comp*>(ptr));
    pool_.SetValue(std::move(v));
  }

  void SetGrowth(GrowthFunc growth) noexcept { pool_.SetGrowth(growth); }

  void GrowExtra(size_type delta_size) { pool_.GrowExtra(delta_size); }

  Xnent& Acquire() { return pool_.Acquire(); }

  void Release(Xnent& obj) noexcept {
    auto& comp = reinterpret_cast<Comp&>(obj);
    auto val = pool_.GetValue();
    if (val) {
      comp = *val;
    } else {
      comp = Comp{};
    }
    pool_.Release(comp);
  }

  size_type Size() const noexcept { return pool_.Size(); }

 private:
  using Pool = util::DynamicPool<Comp>;
  Pool pool_;
};

template <typename ComponentList>
class XnentPool;

template <typename... Xnents>
class XnentPool<XnentList<Xnents...>> final : public IXnentPool {
 public:
  XnentPool() : pool_table_{OneXnentPool<Xnents>{}...} {}

 private:
  using TypeList = tpp::TypeList<Xnents...>;
  using PoolVariant = std::variant<OneXnentPool<Xnents>...>;
  using PoolTable = std::array<PoolVariant, tpp::Size<TypeList>::value>;

  void AddPolicyImpl(size_type init_size, std::unique_ptr<Xnent> value,
                     GrowthFunc growth_func, XnentTypeID id) override {
    std::visit(
        [&](auto&& arg) {
          arg.SetValue(std::move(value));
          arg.SetGrowth(growth_func);
          arg.GrowExtra(init_size);
        },
        pool_table_[id]);
  }

  Xnent& AcquireImpl(XnentTypeID id) override {
    return std::visit(
        [](auto&& arg) -> auto& { return arg.Acquire(); }, pool_table_[id]);
  }

  void ReleaseImpl(XnentTypeID id, Xnent& comp) noexcept override {
    std::visit([&comp](auto&& arg) { arg.Release(comp); }, pool_table_[id]);
  }

  size_type OnePoolSizeImpl(XnentTypeID id) const noexcept override {
    return std::visit([](auto&& arg) { return arg.Size(); }, pool_table_[id]);
  }

  PoolTable pool_table_;
};

}  // namespace internal
}  // namespace einu
