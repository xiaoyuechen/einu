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

#include <absl/container/flat_hash_map.h>
#include <einu-engine/core/eid.h>
#include <einu-engine/core/xnent_type_id.h>

#include <memory>
#include <tuple>
#include <utility>
#include <vector>

namespace einu {
namespace ai {
namespace bt {

enum class Result {
  Success,
  Failure,
  Running,
};

class ArgPack {
 public:
  template <typename... Comps>
  void Set(EID eid, std::tuple<Comps&...> comps) {
    cmp_table.clear();
    (cmp_table[GetXnentTypeID<Comps>()] = &std::get<Comps>(comps), ...);
  }

  template <typename Component>
  Component& GetComponent() const {
    return static_cast<Component&>(*cmp_table.at(GetXnentTypeID<Component>()));
  }

  EID GetEID() const noexcept { return eid; }

 private:
  absl::flat_hash_map<XnentTypeID, Xnent*> cmp_table;
  EID eid;
};

class Node {
 public:
  virtual ~Node() = default;
  virtual Result Run(const ArgPack& args) = 0;
};

class InnerNode : public Node {
 public:
  template <typename T, typename... Args>
  T& AddChild(Args&&... args) {
    children_.push_back(
        std::move(std::make_unique<T>(std::forward<Args>(args)...)));
    return static_cast<T&>(*children_.back());
  }

  std::vector<std::unique_ptr<Node>>& GetChildren() { return children_; }

  const std::vector<std::unique_ptr<Node>>& GetChildren() const {
    return children_;
  }

 private:
  std::vector<std::unique_ptr<Node>> children_;
};

class Root final : public InnerNode {
 public:
  Result Run(const ArgPack& args) override;
};

class Sequence final : public InnerNode {
 public:
  Result Run(const ArgPack& args) override;
};

class Selector final : public InnerNode {
 public:
  Result Run(const ArgPack& args) override;
};

class Inverter final : public InnerNode {
 public:
  Result Run(const ArgPack& args) override;
};

class Succeeder : public InnerNode {
 public:
  Result Run(const ArgPack& args) override;
};

}  // namespace bt
}  // namespace ai
}  // namespace einu
