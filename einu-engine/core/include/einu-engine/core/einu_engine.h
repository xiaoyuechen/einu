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

#include "einu-engine/core/internal/eid_pool.h"
#include "einu-engine/core/internal/entity_manager.h"
#include "einu-engine/core/internal/xnent_pool.h"
#include "einu-engine/core/internal/xnent_type_id_register.h"
#include "einu-engine/core/need_list.h"

#ifdef EINU_CORE_PROFILE
#include "easy/profiler.h"
#endif

namespace einu {

template <typename NeedList>
struct EnginePolicy;

template <typename... Components, typename... Singlenents>
struct EnginePolicy<
    NeedList<XnentList<Components...>, XnentList<Singlenents...>>> {
  using PolicyNeedList =
      NeedList<XnentList<Components...>, XnentList<Singlenents...>>;
};

template <typename EnginePolicy>
class EinuEngine {
 public:
  using EngineNeedList = typename EnginePolicy::PolicyNeedList;
  using EngineComponentList = typename EngineNeedList::ComponentList;
  using SinglenentList = typename EngineNeedList::SinglenentList;

  static constexpr std::size_t ComponentCount() noexcept {
    return tmp::Size<typename ToTypeList<EngineComponentList>::Type>::value;
  }
  static constexpr std::size_t SinglenentCount() noexcept {
    return tmp::Size<typename ToTypeList<SinglenentList>::Type>::value;
  }

  EinuEngine() {
#ifdef EINU_CORE_PROFILE
    EASY_MAIN_THREAD;
    EASY_PROFILER_ENABLE;
    profiler::startListen();
#endif
  }

  ~EinuEngine() {
#ifdef EINU_CORE_PROFILE
    profiler::stopListen();
    profiler::dumpBlocksToFile("test_profile.prof");
#endif
  }

  std::unique_ptr<IXnentPool> CreateComponentPool() {
    using ComponentPool = internal::XnentPool<EngineComponentList>;
    return std::make_unique<ComponentPool>();
  }

  std::unique_ptr<IXnentPool> CreateSinglenentPool() {
    using SinglenentPool = internal::XnentPool<SinglenentList>;
    return std::make_unique<SinglenentPool>();
  }

  std::unique_ptr<IEntityManager> CreateEntityManager() {
    using EntityManager =
        internal::EntityManager<ComponentCount(), SinglenentCount()>;
    return std::make_unique<EntityManager>();
  }

  std::unique_ptr<IEIDPool> CreateEIDPool() {
    return std::make_unique<internal::EIDPool>();
  }

 private:
  internal::XnentTypeIDRegister<EngineComponentList> component_tid_reg_;
  internal::XnentTypeIDRegister<SinglenentList> singlenent_tid_reg_;
};

}  // namespace einu
