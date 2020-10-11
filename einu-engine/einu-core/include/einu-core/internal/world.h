#pragma once

#include <memory>
#include <unordered_map>

#include "einu-core/i_entity_pool.h"
#include "einu-core/i_world.h"

namespace einu {
namespace internal {

class World final : public IWorld {
 public:
  using EntityTable = std::unordered_map<EID, IEntity*>;

  EntityTable& Table() noexcept { return entity_table_; }
  const EntityTable& Table() const noexcept { return entity_table_; }
  IEntity& Singlentity() noexcept { return *singlentity_; }
  const IEntity& Singlentity() const noexcept { return *singlentity_; }

 private:
  void AddEntityImpl(IEntity& ett) override;
  void RemoveEntityImpl(EID eid) override;
  IEntity& GetEntityImpl(EID eid) noexcept override;
  const IEntity& GetEntityImpl(EID eid) const noexcept override;
  std::size_t GetEntityCountImpl() const noexcept override;
  void GetAllEntitiesImpl(EntityBuffer& buffer) const override;
  IEntity& GetSinglenityImpl() noexcept override;
  const IEntity& GetSinglenityImpl() const noexcept override;

  EntityTable entity_table_;
  IEntity* singlentity_ = nullptr;
};

}  // namespace internal
}  // namespace einu