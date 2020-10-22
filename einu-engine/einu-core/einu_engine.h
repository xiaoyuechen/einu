#pragma once

#include "einu-core/internal/eid_pool.h"
#include "einu-core/internal/entity_manager.h"
#include "einu-core/internal/xnent_pool.h"
#include "einu-core/internal/xnent_type_id_register.h"
#include "einu-core/need_list.h"

namespace einu {

template <typename NeedList>
struct EnginePolicy;

template <typename... Components, typename... Singlenents>
struct EnginePolicy<
    NeedList<XnentList<Components...>, XnentList<Singlenents...>>> {
  using NeedList =
      NeedList<XnentList<Components...>, XnentList<Singlenents...>>;
};

template <typename EnginePolicy>
class EinuEngine {
 public:
  using NeedList = typename EnginePolicy::NeedList;
  using ComponentList = typename NeedList::ComponentList;
  using SinglenentList = typename NeedList::SinglenentList;

  static constexpr std::size_t ComponentCount() noexcept {
    return tmp::Size<typename ToTypeList<ComponentList>::Type>::value;
  }
  static constexpr std::size_t SinglenentCount() noexcept {
    return tmp::Size<typename ToTypeList<SinglenentList>::Type>::value;
  }

  EinuEngine() noexcept {}

  std::unique_ptr<IXnentPool> CreateComponentPool() {
    using ComponentPool = internal::XnentPool<ComponentList>;
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
  internal::XnentTypeIDRegister<ComponentList> component_tid_reg_;
  internal::XnentTypeIDRegister<SinglenentList> singlenent_tid_reg_;
};

}  // namespace einu